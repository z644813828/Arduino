// https://voltiq.ru/how-to-use-mqtt-for-smart-home-arduino-esp32/
// https://habr.com/ru/post/680902/

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "display.h"
#include "led.h"
#include "mqtt.h"

const char *ssid = "dd-wrt";
const char *password = "0000000000";
const char *mqtt_server = "192.168.2.254";

/* create an instance of PubSubClient client */
static WiFiClient espClient;
static PubSubClient client(espClient);

/* topics */
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
    Serial.println(strPayload);

    if (strTopic == MQTT_LED_BRIGHT_TOPIC) {
        led_set_brightness(strPayload.toInt());
    } else if (strTopic == MQTT_LED_COLOR_TOPIC) {
        led_set_color(strPayload);
    } else if (strTopic == MQTT_MONIT_TEXT_TOPIC) {
        display_monit_text(strPayload);
        led_set_error_code(strPayload.isEmpty());
    } else if (strTopic == MQTT_LED_ENABLED_TOPIC) {
        led_set_enabled(strPayload.toInt());
    }
}

static bool mqttconnect()
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

static bool wifi_connected()
{
    if (WiFi.status() == WL_CONNECTED) {
        display_wifi_connected(true);
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        client.setServer(mqtt_server, PORT);
        client.setCallback(callback);
        return true;
    }

    display_wifi_connected(false);
}

void mqtt_setup()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
}

void mqtt_loop()
{
    if (!wifi_connected())
        return;

    if (!mqttconnect())
        return;
}
