#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define HTTP_REQUEST_COLOR "color"

class Wifi {
  public:
    static Wifi &Instance();

    Wifi();

    void setup();
    void loop();

    bool getStatus() { return m_wifiStatus; }

  private:
    void InitHandler();

    bool m_wifiStatus = false;
    AsyncWebServer m_server;
};
#endif
