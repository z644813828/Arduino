#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define HTTP_REQUEST_COLOR "color"
#define HTTP_REQUEST_EFFECT "effect"
#define HTTP_REQUEST_BRIGHTNESS "brightness"
#define HTTP_REQUEST_ERROR_EFFECT "error_effect"
#define HTTP_REQUEST_EFFECT_ARG "effect_arg_"
#define HTTP_REQUEST_SOIL_WETNESS "soil_wetness"
#define HTTP_REQUEST_LED_DEBUG "debug_led"
#define HTTP_REQUEST_DISPLAY_TEST "display_test"
#define HTTP_REQUEST_MOTION_TIMEOUT "motion_timeout"
#define HTTP_REQUEST_REBOOT "reboot"
#define HTTP_REQUEST_DISPLAY_BRIGHTNESS "display_brightness"
#define HTTP_REQUEST_DISPLAY_OFF_BRIGHTNESS "display_off_brightness"

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
    ESP8266WebServer m_server;
};
#endif
