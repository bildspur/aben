#include <Arduino.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <inttypes.h>
#include <controller/interaction/PIRArrayInteraction.h>
#include <controller/scene/interaction/PortalScene.h>
#include <controller/scene/AbenSceneController.h>
#include <controller/scene/show/ShowScene.h>

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
auto portalScene = PortalScene(&installation);
auto showScene = ShowScene(&installation);
auto sceneController = AbenSceneController(&installation, &portalScene, &showScene);

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

// vars
bool sendOSCFeedback = false;
bool updateColor = false;

// methods
void handleOsc(OSCMessage &msg);

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

void handleOsc(OSCMessage &msg) {
    sendOSCFeedback = false;
    updateColor = false;

    // color
    msg.dispatch("/aben/color/hue", [](OSCMessage &msg) {
        installation.getSettings().setDefaultHue(msg.getFloat(0));
        sendOSCFeedback = true;
        updateColor = true;
    });

    msg.dispatch("/aben/color/saturation", [](OSCMessage &msg) {
        installation.getSettings().setDefaultSaturation(msg.getFloat(0));
        sendOSCFeedback = true;
        updateColor = true;
    });

    msg.dispatch("/aben/installation/red", [](OSCMessage &msg) {
        for (int i = 0; i < installation.getSize(); i++) {
            installation.getPortal(i)->getLed()->setRGB(RGBColor(1.0f, 0.0f, 0.0f));
        }
    });

    msg.dispatch("/aben/installation/green", [](OSCMessage &msg) {
        for (int i = 0; i < installation.getSize(); i++) {
            installation.getPortal(i)->getLed()->setRGB(RGBColor(0.0f, 1.0f, 0.0f));
        }
    });

    msg.dispatch("/aben/installation/blue", [](OSCMessage &msg) {
        for (int i = 0; i < installation.getSize(); i++) {
            installation.getPortal(i)->getLed()->setRGB(RGBColor(0.0f, 0.0f, 1.0f));
        }
    });

    // installation
    msg.dispatch("/aben/activationtime", [](OSCMessage &msg) {
        installation.getSettings().setPortalActivationTime(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
        sendOSCFeedback = true;
    });

    // global
    msg.dispatch("/aben/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setMinBrightness(msg.getFloat(0));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setMaxBrightness(msg.getFloat(0));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/gamma/on", [](OSCMessage &msg) {
        installation.getSettings().setGammaCorrection(!installation.getSettings().isGammaCorrection());
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/scenemanager/on", [](OSCMessage &msg) {
        sceneController.setRunning(!sceneController.isRunning());
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/interaction/on", [](OSCMessage &msg) {
        installation.getSettings().setInteractionOn(!installation.getSettings().isInteractionOn());
        sendOSCFeedback = true;
    });

    // time star
    msg.dispatch("/aben/timestar/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinBrightness(msg.getFloat(0));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/timestar/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxBrightness(msg.getFloat(0));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/timestar/randomFactor", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarRandomOnFactor(msg.getFloat(0));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/timestar/duration/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/timestar/duration/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
        sendOSCFeedback = true;
    });

    // controls
    msg.dispatch("/aben/installation/on", [](OSCMessage &msg) {
        sceneController.setRunning(false);
        installation.turnOn();
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/installation/off", [](OSCMessage &msg) {
        sceneController.setRunning(false);
        installation.turnOff();
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/refresh", [](OSCMessage &msg) {
        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/settings/load", [](OSCMessage &msg) {
        installation.loadFromEEPROM();
        osc.send("/aben/status", "Status: loaded");
        sendOSCFeedback = true;
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
        sendOSCFeedback = true;
    });

    // portal settings
    msg.dispatch("/aben/portal/threshold", [](OSCMessage &msg) {
        installation.getSettings().setPortalMinTreshold(msg.getFloat(0));

        // send portal values
        osc.send("/aben/portal/threshold", installation.getSettings().getPortalMinTreshold());

        sendOSCFeedback = true;
    });

    msg.dispatch("/aben/portal/debug/activate", [](OSCMessage &msg) {
        int id = static_cast<int>(msg.getFloat(0));
        Serial.printf("portal %d actived by debug console\n", id);
        installation.getPortal(id)->setActivated(true);
        sendOSCFeedback = true;
    });

    // portal
    msg.dispatch("/aben/portal/online", [](OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->onlineStateReceived();
        Serial.printf("portal %d: online\n", id);
    });

    msg.dispatch("/aben/portal/activated", [](OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->setActivated(true);
        Serial.printf("portal %d: activated\n", id);
    });

    if (sendOSCFeedback) {
        sendRefresh();
    }

    if (updateColor) {
        // update hsv color
        for (int i = 0; i < installation.getSize(); i++) {
            installation.getPortal(i)->getLed()->setHSV(
                    HSVColor(installation.getSettings().getDefaultHue(),
                             installation.getSettings().getDefaultSaturation(),
                             installation.getSettings().getMaxBrightness())
            );
        }
    }
}

void sendRefresh() {
    // global
    osc.send("/aben/brightness/min", installation.getSettings().getMinBrightness());
    osc.send("/aben/brightness/max", installation.getSettings().getMaxBrightness());

    osc.send("/aben/gamma/on", installation.getSettings().isGammaCorrection());
    osc.send("/aben/scenemanager/on", sceneController.isRunning());
    osc.send("/aben/interaction/on", installation.getSettings().isInteractionOn());

    osc.send("/aben/version", installation.getSettings().getVersion());

    // installation
    osc.send("/aben/activationtime",
             static_cast<float>(MathUtils::millisToSeconds(installation.getSettings().getPortalActivationTime())));

    // colors
    osc.send("/aben/color/hue", installation.getSettings().getDefaultHue());
    osc.send("/aben/color/saturation", installation.getSettings().getDefaultSaturation());

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

    // send portal updates
    for (auto i = 0; i < installation.getSize(); i++) {
        auto portal = installation.getPortal(i);
        auto portalAddress = String("/aben/portal/") + String(portal->getId()) + String("/").c_str();

        osc.send((String(portalAddress.c_str()) + "online").c_str(), portal->isOnline());
        osc.send((String(portalAddress.c_str()) + "activated").c_str(), portal->isActivated());
    }
}