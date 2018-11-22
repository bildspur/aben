//
// Created by Florian on 09.10.18.
//

#include <HardwareSerial.h>
#include "SerialLightRenderer.h"

SerialLightRenderer::SerialLightRenderer(Installation *installation)
        : LightRenderer(installation, SERIAL_RENDER_FRAMERATE) {

}

void SerialLightRenderer::setup() {
    LightRenderer::setup();

    watch.start();
}

void SerialLightRenderer::timedLoop() {
    LightRenderer::loop();

    String msg = "SLR;";

    for (int i = 0; i < installation->getSize(); i++) {
        auto r = mapToGlobalBrightnessRange(installation->getPortal(i)->getLed()->getRed());
        auto g = mapToGlobalBrightnessRange(installation->getPortal(i)->getLed()->getGreen());
        auto b = mapToGlobalBrightnessRange(installation->getPortal(i)->getLed()->getBlue());

        msg += String(r) + " ";
        msg += String(g) + " ";
        msg += String(b) + ";";
    }

    msg += "\n";
    Serial.println(msg);

    if (debugTimer.elapsed()) {
        auto led = installation->getPortal(0)->getLed();
        Serial.printf("R:%f G:%f B:%f\n", led->getRed(), led->getGreen(), led->getBlue());
    }
}

void SerialLightRenderer::render(PortalPtr portal) {
    LightRenderer::render(portal);
}
