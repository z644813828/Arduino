#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>

#include "display.h"
#include "led.h"
#include "mqtt.h"

const char *ssid = "ASUS";
const char *password = "5259alpha1";
const char *mqtt_server = "192.168.2.254";

static bool wifi_status = false;

#define HTTP_REQUEST_COLOR "color"

static WiFiClient espClient;
static PubSubClient client(espClient);

AsyncWebServer server(80);

#define MQTT_LED_ENABLED_TOPIC "led/enabled"
#define MQTT_LED_BRIGHT_TOPIC "led/bright"
#define MQTT_LED_COLOR_TOPIC "led/color"
#define MQTT_MONIT_TEXT_TOPIC "monit/text"

#define PORT 1883

static void callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';
    Serial.print(topic);
    Serial.print("  ");
    String strTopic = String(topic);
    String strPayload = String((char *)payload);
    strPayload.replace("\n", " ");
    Serial.println(strPayload);

    if (strTopic == MQTT_LED_BRIGHT_TOPIC) {
        // led_set_brightness(strPayload.toInt());
    } else if (strTopic == MQTT_LED_COLOR_TOPIC) {
        // led_set_color(strPayload);
    } else if (strTopic == MQTT_MONIT_TEXT_TOPIC) {
        display_monit_text(strPayload);
        // led_set_error_code(strPayload.isEmpty());
    } else if (strTopic == MQTT_LED_ENABLED_TOPIC) {
        // led_set_enabled(strPayload.toInt());
    }
}

static void init_webserver_handler()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
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
        // str += led_get_html_colors();
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

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam(HTTP_REQUEST_COLOR)) {
            // led_set_color(request->getParam(HTTP_REQUEST_COLOR)->value());
        }

        request->redirect("/");
    });
}

static bool wifi_connected()
{
    bool new_status = WiFi.status() == WL_CONNECTED;

    if (new_status != wifi_status) {
        if (new_status) {
            Serial.println("WiFi Connected");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            client.setServer(mqtt_server, PORT);
            client.setCallback(callback);

            init_webserver_handler();
            server.begin();
        } else {
            Serial.println("WiFi Disconnected");
        }
    }

    wifi_status = new_status;
    display_wifi_connected(wifi_status);
    return wifi_status;
}

static bool mqtt_connect()
{
    if (client.connected()) {
        display_mqtt_connected(true);
        return true;
    }

    display_mqtt_connected(false);

    String clientId = "ESP32Client";

    if (client.connect(clientId.c_str())) {
        Serial.println("MQTT connected");
        client.subscribe(MQTT_LED_BRIGHT_TOPIC);
        client.subscribe(MQTT_LED_COLOR_TOPIC);
        client.subscribe(MQTT_LED_ENABLED_TOPIC);
        client.subscribe(MQTT_MONIT_TEXT_TOPIC);
    } else {
        Serial.print("MQTT connection failed, status code =");
        Serial.println(client.state());
    }
    return false;
}

void mqtt_setup()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.hostname("Name");
    WiFi.begin(ssid, password);
}

void mqtt_loop()
{
    if (!wifi_connected())
        return;

    if (!mqtt_connect())
        return;

    client.loop();
}
