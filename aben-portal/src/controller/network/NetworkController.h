//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_NETWORKCONTROLLER_H
#define SILVA_NETWORKCONTROLLER_H

#ifdef ESP32

#include <WiFi.h>

#elif defined(ESP8266)

#include <ESP8266WiFi.h>

#endif // ESP32

#include "../BaseController.h"

#define STA_MAX_DELAYS 50

class NetworkController : public BaseController {
private:
    const char *deviceName;
    const char *ssid;
    const char *password;

    WiFiMode_t wifiMode;

    void initSTA();

    void setupSTA();

    void setupAP();

    void setupMDNS();

    String getIPAddress();

public:
    NetworkController(const char *deviceName, const char *ssid, const char *password, WiFiMode_t wifiMode = WIFI_AP);

    void setup() override;

    void loop() override;

    void printNetworkInformation();

    void addMDNSService(const char *service, const char *proto, uint16_t port);

    void addMDNSServiceTxt(String name, String proto, String key, String value);
};


#endif //SILVA_NETWORKCONTROLLER_H
