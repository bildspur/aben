//
// Created by Florian on 27.11.17.
//

#ifdef ESP32

#include <ESPmDNS.h>

#elif defined(ESP8266)

#include <ESP8266mDNS.h>
#include <util/StatusLed.h>

#endif // ESP32

#include "NetworkController.h"

NetworkController::NetworkController(const char *deviceName, const char *ssid, const char *password,
                                     WiFiMode_t wifiMode) {
    this->deviceName = deviceName;
    this->ssid = ssid;
    this->password = password;
    this->wifiMode = wifiMode;
}

void NetworkController::setup() {
    BaseController::setup();

    // disconnect first
    WiFi.disconnect(true);

    if (wifiMode == WIFI_STA) {
        initSTA();
        setupSTA();
    } else {
        setupAP();
    }

#ifdef ESP32
    WiFi.setHostname(deviceName);
#elif defined(ESP8266)
    WiFi.hostname(deviceName);
#endif // ESP32

    setupMDNS();

    printNetworkInformation();
}

void NetworkController::loop() {
    BaseController::loop();

    // check for connection loss
    if (wifiMode == WIFI_STA && WiFi.status() != WL_CONNECTED) {
        Serial.println("lost connection...");
        setup();
    }
}

void NetworkController::initSTA() {
    Serial.println("init STA mode...");

    StatusLed::turnOn();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    StatusLed::turnOff();
}

void NetworkController::setupSTA() {
    uint8_t waitedDelays = 0;

    // wait till wifi is connected
    while (WiFi.status() != WL_CONNECTED) {
        StatusLed::turnOn();
        waitedDelays++;

        // reset wifi
        if (waitedDelays > STA_MAX_DELAYS) {
            Serial.println();
            Serial.println("re-init wifi...");
            initSTA();
            waitedDelays = 0;
        }

        StatusLed::turnOff();
        delay(150);
        StatusLed::turnOn();
        delay(150);
        StatusLed::turnOff();
    }

    Serial.println("connected!");
    StatusLed::turnOn();
}

void NetworkController::setupAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
}

void NetworkController::setupMDNS() {
    if (!MDNS.begin(deviceName)) {
        Serial.println("Error setting up MDNS responder!");
    }

    // Add service to MDNS-SD
    MDNS.addServiceTxt("_osc", "_udp", "mac", WiFi.macAddress());
}

void NetworkController::printNetworkInformation() {
    Serial.print("WiFi State: ");
    Serial.println(WiFi.status());

    Serial.print("Local IP address: ");
    Serial.println(getIPAddress());

    Serial.print("Mac Address: ");
    Serial.println(WiFi.macAddress());
}


String NetworkController::getIPAddress() {
    if (wifiMode == WIFI_AP)
        return WiFi.softAPIP().toString();
    else
        return WiFi.localIP().toString();
}

void NetworkController::addMDNSService(const char *service, const char *proto, uint16_t port) {
    MDNS.addService(service, proto, port);
}

void NetworkController::addMDNSServiceTxt(String name, String proto, String key, String value) {
    MDNS.addServiceTxt(name.c_str(), proto.c_str(), key.c_str(), value.c_str());
}
