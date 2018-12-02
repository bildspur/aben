#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>
#include <controller/interaction/RemoteMotionDetector.h>
#include "controller/BaseController.h"
#include "controller/app/App.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "util/MathUtils.h"

// global

// id rotatry
#define ID_0BIT_PIN D3
#define ID_2BIT_PIN D2
#define ID_4BIT_PIN D1

// motion sensor
#define MOTION_TRIGGER_PIN D6
#define MOTION_ECHO_PIN D7

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME "aben-master"

#define SSID_NAME "aben"
#define SSID_PASSWORD "ABENbildspur"

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

// twisted
#define OSC_OUT_PORT 8000
#define OSC_IN_PORT 9000

// typedefs
typedef BaseController *BaseControllerPtr;
auto app = App();

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// sensors
auto motionSensor = RemoteMotionDetector(&app, &osc, MOTION_TRIGGER_PIN, MOTION_ECHO_PIN);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        &app,
        &motionSensor
};

// methods
void handleOsc(OSCMessage &msg);

void sendRefresh();

void setup() {
    Serial.begin(BAUD_RATE);

    // wait some seconds for debugging
    delay(1000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // load settings
    app.loadFromEEPROM();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    network.addMDNSService("_osc", "_udp", OSC_IN_PORT);

    Serial.println("setup finished!");
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void handleOsc(OSCMessage &msg) {
    // global
    /*
    msg.dispatch("/aben/brightness/min", [](OSCMessage &msg) {

    });
    */
}

void sendRefresh() {
    // global
    osc.send("/aben/portal/online", app.getSettings().getPortalId());
}