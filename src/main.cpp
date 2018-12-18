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
    oscRouter.onReceive(msg);
}

void sendRefresh() {
    oscRouter.publishAll();
}