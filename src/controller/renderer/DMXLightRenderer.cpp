#include <cmath>

//
// Created by Florian Bruggisser on 21.10.18.
//

#include <esp_task_wdt.h>
#include <model/light/Led.h>
#include "DMXLightRenderer.h"
#include "../../util/MathUtils.h"
#include "../driver/LXESP32DMX/LXESP32DMX.h"

DMXLightRenderer::DMXLightRenderer(uint8_t txPin, uint8_t lightAddressSize, Installation *installation)
        : LightRenderer(installation, installation->getSettings()->getAppFrameRate()) {
    this->lightChannelSize = lightAddressSize;
    this->txPin = txPin;
}

void DMXLightRenderer::setup() {
    LightRenderer::setup();

    pinMode(txPin, OUTPUT);
    ESP32DMX.startOutput(txPin);

    clearDMXBuffer();
}

void DMXLightRenderer::timedLoop() {
    LightRenderer::timedLoop();

    // send dmx bulk
    publishBuffer();
}

void DMXLightRenderer::render(PortalPtr portal) {
    LightRenderer::render(portal);

    // get address => + 1 because buffer starts at 1 not 0
    auto address = portal->getId() * lightChannelSize + 1;

    for (int i = 0; i < portal->getLed()->getChannelCount(); i++) {
        // map global brightness
        auto brightness = mapToGlobalBrightnessRange(portal->getLed()->getRGBChannel(static_cast<unsigned int>(i)));

        // convert to dmx
        auto dmxValue = static_cast<uint8_t>(std::lround(
                MathUtils::map(brightness, LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS, DMX_MIN_VALUE, DMX_MAX_VALUE)
        ));

        // apply gamma correction if needed
        if (installation->getSettings()->isGammaCorrection())
            dmxValue = gamma8[dmxValue];

        // weird controller mapping: K1 => 4, K4 => 1
        dmxBuffer[address + 3 - i] = dmxValue;
    }
}

void DMXLightRenderer::publishBuffer() {
    xSemaphoreTake(ESP32DMX.lxDataLock, portMAX_DELAY);
    for (int i = 1; i < DMX_MAX_FRAME; i++) {
        ESP32DMX.setSlot(i, dmxBuffer[i]);
    }
    xSemaphoreGive(ESP32DMX.lxDataLock);
}

void DMXLightRenderer::clearDMXBuffer() {
// clear buffer
    for (int i = 1; i < DMX_MAX_FRAME; i++) {
        dmxBuffer[i] = 0;
    }
}
