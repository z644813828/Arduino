#include <ESP8266WiFi.h>

// Network SSID
const char *ssid = "ASUS";
const char *password = "5259alpha1";

bool last_status_connected = false;

static bool wifi_connected()
{
    if (WiFi.status() == WL_CONNECTED) {
        // display_wifi_connected(true);
        if (!last_status_connected) {
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
        }
        last_status_connected = true;

        // client.setServer(mqtt_server, PORT);
        // client.setCallback(callback);
        return true;
    }

    // display_wifi_connected(false);
}

void mqtt_setup()
{
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // Connect WiFi
    WiFi.hostname("Name");
    WiFi.begin(ssid, password);
}

void mqtt_loop()
{
    if (!wifi_connected())
        return;

    //  if (!mqttconnect())
    //   return;
}
