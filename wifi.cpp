#include "display.h"
#include "led.h"
#include "mqtt.h"
#include "wifi.h"

#include "secrets.h"

Wifi::Wifi()
    : m_server(80)
{
}

Wifi &Wifi::Instance()
{
    static Wifi instance;
    return instance;
}

void Wifi::setup()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.hostname("Name");
    WiFi.begin(SSID, PASSWORD);
}

void Wifi::InitHandler()
{
    m_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String str;
        str += "<!DOCTYPE html>\n";
        str += "<html>\n";
        str += "<body>\n";
        str += "\n";
        str += "<h1>Mqtt Client</h1>\n";
        str += "\n";
        str += "<form action=\"/get\">\n";
        str += "  <label for=\"color\">Color:</label>\n";
        str += "   <select name=\"color\" id=\"color\">\n";
        str += Led::Instance().getHtmlColors();
        str += "   </select>\n";
        str += "  <br><br>\n";
        str += "  <input type=\"submit\" value=\"Submit\">\n";
        str += "</form>\n";
        str += "\n";
        str += "\n";
        str += "</body>\n";
        str += "</html>\n";

        request->send_P(200, "text/html", str.c_str());
    });

    m_server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam(HTTP_REQUEST_COLOR)) {
            String color = request->getParam(HTTP_REQUEST_COLOR)->value();
            Led::Instance().setColor(color);
            Mqtt::Instance().set(String(MQTT_LED_COLOR_TOPIC), color);
        }

        request->redirect("/");
    });
}

void Wifi::loop()
{
    bool new_status = WiFi.status() == WL_CONNECTED;

    if (new_status != m_wifiStatus) {
        if (new_status) {
            Serial.println("WiFi Connected");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());

            InitHandler();
            m_server.begin();
        } else {
            Serial.println("WiFi Disconnected");
        }
    }

    m_wifiStatus = new_status;
    Display::Instance().setWifiConnected(m_wifiStatus);
}
