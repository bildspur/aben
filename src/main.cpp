#include <Arduino.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <inttypes.h>
#include <controller/interaction/PIRArrayInteraction.h>

#include "controller/BaseController.h"
#include "model/Portal.h"
#include "controller/app/Installation.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "controller/renderer/LightRenderer.h"
#include "controller/scene/BaseScene.h"
#include "controller/scene/SceneController.h"
#include "controller/renderer/SerialLightRenderer.h"
#include "controller/renderer/DMXLightRenderer.h"
#include "controller/scene/star/TimeStarScene.h"
#include "util/MathUtils.h"

// global
#define PORTAL_COUNT 5

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME "aben-master"

#define SSID_NAME "aben"
#define SSID_PASSWORD "ABENbildspur"

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

// dmx
#define DMX_TX_PIN 25
#define DMX_LIGHT_ADDRESS_SIZE 4

// typedefs
typedef BaseController
        *
        BaseControllerPtr;
typedef Portal *PortalPtr;

// variables
PortalPtr portals[PORTAL_COUNT];
auto installation = Installation(PORTAL_COUNT, portals);

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_AP);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// renderer
LightRenderer *renderer = new DMXLightRenderer(DMX_TX_PIN, DMX_LIGHT_ADDRESS_SIZE, &installation);
LightRenderer *debugRenderer = new SerialLightRenderer(&installation);

// scenes
TimeStarScene timeStarScene = TimeStarScene(&installation);
auto sceneController = SceneController(&installation, &timeStarScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        debugRenderer,
        renderer,
        &sceneController,
        &installation
};

// methods
void handleOsc(OSCMessage &msg);

void changeScene(BaseScene *scene);

void sendRefresh();

void setup() {
    Serial.begin(BAUD_RATE);

    // wait some seconds for debugging
    delay(5000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // setup portals
    installation.initPortals();

    // load settings
    installation.loadFromEEPROM();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("_osc", "_udp", OSC_IN_PORT);

    Serial.println("setup finished!");
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void changeScene(BaseScene *scene) {
    sceneController.setActiveScene(scene);

    // setup scene
    sceneController.getActiveScene()->setup();
}

void handleOsc(OSCMessage &msg) {
    // global
    msg.dispatch("/aben/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setMinBrightness(msg.getFloat(0));
    });

    msg.dispatch("/aben/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setMaxBrightness(msg.getFloat(0));
    });

    msg.dispatch("/aben/gamma/on", [](OSCMessage &msg) {
        installation.getSettings().setGammaCorrection(!installation.getSettings().isGammaCorrection());
    });

    msg.dispatch("/aben/scenemanager/on", [](OSCMessage &msg) {
        sceneController.setRunning(!sceneController.isRunning());
    });

    // time star
    msg.dispatch("/aben/timestar/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinBrightness(msg.getFloat(0));
    });

    msg.dispatch("/aben/timestar/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxBrightness(msg.getFloat(0));
    });

    msg.dispatch("/aben/timestar/randomFactor", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarRandomOnFactor(msg.getFloat(0));
    });

    msg.dispatch("/aben/timestar/duration/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
    });

    msg.dispatch("/aben/timestar/duration/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
    });

    // controls
    msg.dispatch("/aben/installation/on", [](OSCMessage &msg) {
        sceneController.setRunning(false);
        installation.turnOn();
    });

    msg.dispatch("/aben/installation/off", [](OSCMessage &msg) {
        sceneController.setRunning(false);
        installation.turnOff();
    });

    msg.dispatch("/aben/refresh", [](OSCMessage &msg) {
        sendRefresh();
    });

    msg.dispatch("/aben/settings/load", [](OSCMessage &msg) {
        installation.loadFromEEPROM();
        osc.send("/aben/status", "Status: loaded");
    });

    msg.dispatch("/aben/settings/save", [](OSCMessage &msg) {
        installation.saveToEEPROM();
        osc.send("/aben/portal/save", 0);
        osc.send("/aben/status", "Status: saved");
    });

    msg.dispatch("/aben/settings/default", [](OSCMessage &msg) {
        installation.loadDefaultSettings();

        // send portal values
        osc.send("/aben/portal/threshold", installation.getSettings().getPortalMinTreshold());

        // send back update info
        osc.send("/aben/status", "Status: default");
    });

    // portal settings
    msg.dispatch("/aben/portal/threshold", [](OSCMessage &msg) {
        installation.getSettings().setPortalMinTreshold(msg.getFloat(0));
    });

    // portal
    msg.dispatch("/aben/portal/online", [](OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->onlineStateReceived();
        Serial.printf("portal %d is online!\n", id);
    });

    msg.dispatch("/aben/portal/active", [](OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->setActivated(true);
        Serial.printf("portal %d activated!\n", id);
    });

    sendRefresh();
}

void sendRefresh() {
    // global
    osc.send("/aben/brightness/min", installation.getSettings().getMinBrightness());
    osc.send("/aben/brightness/max", installation.getSettings().getMaxBrightness());

    osc.send("/aben/gamma/on", installation.getSettings().isGammaCorrection());
    osc.send("/aben/scenemanager/on", sceneController.isRunning());

    osc.send("/aben/version", installation.getSettings().getVersion());

    // time star
    osc.send("/aben/timestar/brightness/min", installation.getSettings().getTimeStarMinBrightness());
    osc.send("/aben/timestar/brightness/max", installation.getSettings().getTimeStarMaxBrightness());
    osc.send("/aben/timestar/randomFactor", installation.getSettings().getTimeStarRandomOnFactor());
    osc.send("/aben/timestar/duration/min",
             static_cast<float>(MathUtils::millisToSeconds(installation.getSettings().getTimeStarMinDuration())));
    osc.send("/aben/timestar/duration/max",
             static_cast<float>(MathUtils::millisToSeconds(installation.getSettings().getTimeStarMaxDuration())));

    // portal
    osc.send("/aben/portal/threshold", installation.getSettings().getPortalMinTreshold());
}