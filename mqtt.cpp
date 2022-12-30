// https://voltiq.ru/how-to-use-mqtt-for-smart-home-arduino-esp32/
// https://habr.com/ru/post/680902/

// monit summary | grep "failed" | awk '{ print $1 }

#include "display.hpp"
#include "led.hpp"
#include "mqtt.hpp"

#ifdef ARDUINO

const char *ssid = "dd-wrt";
const char *password = "0000000000";
const char *mqtt_server = "192.168.2.254";

/* create an instance of PubSubClient client */
static WiFiClient espClient;
static PubSubClient client(espClient);

/* topics */
#define LED_BRIGHT_TOPIC "SERVER/led/bright"
#define LED_COLOR_TOPIC "SERVER/led/color"
#define LED_MONIT_CODE_TOPIC "SERVER/monit/code"
#define LED_MONIT_TEXT_TOPIC "SERVER/monit/text"

#define PORT 1883

static void callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';
    Serial.print(topic);
    Serial.print("  ");
    String strTopic = String(topic);
    String strPayload = String((char *)payload);
    Serial.println(strPayload);

    if (strTopic == LED_BRIGHT_TOPIC) {
        led_set_brightness(strPayload.toInt());
    } else if (strTopic == LED_COLOR_TOPIC) {
        led_set_color(strPayload);
    } else if (strTopic == LED_MONIT_CODE_TOPIC) {
        led_set_error_code(strPayload.toInt());
    } else if (strTopic == LED_MONIT_TEXT_TOPIC) {
        display_set_text(strPayload);
    }
}

static void mqttconnect()
{
    /* Loop until reconnected */
    while (!client.connected()) {
        Serial.print("MQTT connecting ...");
        /* client ID */
        String clientId = "ESP32Client";
        /* connect now */
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            /* subscribe topic with default QoS 0*/
            client.subscribe(LED_BRIGHT_TOPIC);
            client.subscribe(LED_COLOR_TOPIC);
            client.subscribe(LED_MONIT_CODE_TOPIC);
            client.subscribe(LED_MONIT_TEXT_TOPIC);
        } else {
            Serial.print("failed, status code =");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            /* Wait 5 seconds before retrying */
            delay(5000);
        }
    }
}

void mqtt_setup()
{
    Serial.begin(115200);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* configure the MQTT server with IPaddress and port */
    client.setServer(mqtt_server, PORT);
    client.setCallback(callback);
}

void mqtt_loop()
{
    /* if client was disconnected then try to reconnect again */
    if (!client.connected()) {
        mqttconnect();
    }
}
#else
void mqtt_loop() {}
void mqtt_setup() {}

#endif
