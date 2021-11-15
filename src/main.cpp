#undef min
#undef max

#include <Arduino.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <inttypes.h>
#include <controller/interaction/PIRArrayInteraction.h>
#include <controller/scene/interaction/PortalScene.h>
#include <controller/scene/AbenSceneController.h>
#include <controller/scene/show/ShowScene.h>
#include <data/model/DataModel.h>
#include <data/eeprom/EEPROMStorage.h>
#include <data/osc/OSCDataRouter.h>
#include <data/osc/rule/OSCInputAction.h>
#include <data/osc/rule/OSCOutputAction.h>

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

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_AP);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// data
auto oscRouter = OSCDataRouter(&osc);

// variables
PortalPtr portals[PORTAL_COUNT];
auto installation = Installation(PORTAL_COUNT, portals, &oscRouter);

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

// methods
void handleOsc(OSCMessage &msg);

void sendRefresh();

void setupOSCActions();

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
    installation.loadStats();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("_osc", "_udp", OSC_IN_PORT);

    setupOSCActions();

    Serial.printf("setup finished (V: %d)\n", installation.getSettings()->getVersion());
    Serial.printf("OSC Rule Count: %d\n", oscRouter.getRules().size());
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void setupOSCActions() {
    oscRouter.addRule(new OSCOutputAction("/aben/portal/status", [](IOSCPublisher *publisher) {
        for (auto i = 0; i < installation.getSize(); i++) {
            auto portal = installation.getPortal(i);
            auto portalAddress = String("/aben/portal/") + String(portal->getId()) + String("/").c_str();

            osc.send((String(portalAddress.c_str()) + "online").c_str(), portal->isOnline());
            osc.send((String(portalAddress.c_str()) + "activated").c_str(), portal->isActivated());
        }
    }));

    oscRouter.addRule(new OSCInputAction("/aben/refresh", [](IOSCPublisher *publisher, OSCMessage &msg) {
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/show/start", [](IOSCPublisher *publisher, OSCMessage &msg) {
        for (int i = 0; i < installation.getSize(); i++) {
            installation.getPortal(i)->setActivated(true);
        }
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/stats/reset", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.resetStats();
        sendRefresh();
    }));

    // hue control
    auto updateLights = [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.turnOn();
    };
    oscRouter.addRule(new OSCInputAction("/aben/color/hue", updateLights));
    oscRouter.addRule(new OSCInputAction("/aben/color/saturation", updateLights));

    oscRouter.addRule(new OSCInputAction("/aben/installation/on", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.getSettings()->setSceneControllerOn(false);
        installation.turnOn();
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/installation/off", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.getSettings()->setSceneControllerOn(false);
        installation.turnOff();
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/settings/load", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.loadFromEEPROM();
        osc.send("/aben/status", "Status: loaded");
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/settings/save", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.saveToEEPROM();
        installation.saveStats();

        osc.send("/aben/portal/save", 0);
        osc.send("/aben/status", "Status: saved");
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/settings/default", [](IOSCPublisher *publisher, OSCMessage &msg) {
        installation.loadDefaultSettings();

        // send portal values
        osc.send("/aben/portal/threshold", installation.getSettings()->getPortalMinTreshold());

        // send back update info
        osc.send("/aben/status", "Status: default");
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/portal/debug/activate", [](IOSCPublisher *publisher, OSCMessage &msg) {
        int id = static_cast<int>(msg.getFloat(0));
        Serial.printf("portal %d actived by debug console\n", id);
        installation.getPortal(id)->setActivated(true);
        sendRefresh();
    }));

    oscRouter.addRule(new OSCInputAction("/aben/portal/online", [](IOSCPublisher *publisher, OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->onlineStateReceived();
        Serial.printf("portal %d: online\n", id);
    }));

    oscRouter.addRule(new OSCInputAction("/aben/portal/activated", [](IOSCPublisher *publisher, OSCMessage &msg) {
        auto id = msg.getInt(0);
        installation.getPortal(id)->setActivated(true);
        installation.getSettings()->incActivatedPortalStats(static_cast<unsigned int>(id));
        Serial.printf("portal %d: activated\n", id);
    }));
}

void handleOsc(OSCMessage &msg) {
    oscRouter.onReceive(msg);
}

void sendRefresh() {
    oscRouter.publishAll();
}