#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>
#include <controller/interaction/RemoteMotionDetector.h>
#include <util/PinReader.h>
#include <util/StatusLed.h>
#include <controller/network/HeartBeat.h>
#include "controller/BaseController.h"
#include "controller/app/App.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "util/MathUtils.h"

// global
#define FIX_PORTAL_ID 0

// status
#define STATUS_LED_PIN 2

// motion sensor
#define MOTION_TRIGGER_PIN D6
#define MOTION_ECHO_PIN D7

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME String("aben-portal-" + FIX_PORTAL_ID)

#define SSID_NAME "aben"
#define SSID_PASSWORD "ABENbildspur"

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

#define HEARTBEAT_TIME 10000

// twisted
#define OSC_OUT_PORT 8000
#define OSC_IN_PORT 9000

// typedefs
typedef BaseController *BaseControllerPtr;
auto app = App();

// controllers
auto network = NetworkController(DEVICE_NAME.c_str(), SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME.c_str(), OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);
auto heartBeat = HeartBeat(HEARTBEAT_TIME);

// sensors
auto motionSensor = RemoteMotionDetector(&app, &osc, MOTION_TRIGGER_PIN, MOTION_ECHO_PIN);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        &app,
        &motionSensor,
        &heartBeat
};

// methods
void handleOsc(OSCMessage &msg);

void sendRefresh();

void setup() {
    Serial.begin(BAUD_RATE);
    StatusLed::setup(STATUS_LED_PIN);

    // wait some seconds for debugging
    delay(5000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // load settings
    app.loadFromEEPROM();

    // set portal id
    app.getSettings().setPortalId(FIX_PORTAL_ID);

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);
    heartBeat.onHeartbeat(sendRefresh);

    // add osc mdns
    network.addMDNSService("_osc", "_udp", OSC_IN_PORT);

    Serial.printf("setup of portal %d finished!", app.getSettings().getPortalId());
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void handleOsc(OSCMessage &msg) {
    // set threshold
    msg.dispatch("/aben/portal/threshold", [](OSCMessage &msg) {
        app.getSettings().setMinThreshold(msg.getFloat(0));
    });

    // save settings
    msg.dispatch("/aben/portal/save", [](OSCMessage &msg) {
        app.saveToEEPROM();
    });

    // receive settings
    msg.dispatch("/aben/portal/settings", [](OSCMessage &msg) {
        auto portalAddress = String("/aben/portal/") + String(app.getSettings().getPortalId()) + String("/");

        osc.send((String(portalAddress.c_str()) + "version").c_str(), app.getSettings().getVersion());
        osc.send((String(portalAddress.c_str()) + "threshold").c_str(), app.getSettings().getMinThreshold());
    });
}

void sendRefresh() {
    // send online state
    osc.send("/aben/portal/online", app.getSettings().getPortalId());
}