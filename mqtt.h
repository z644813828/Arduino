#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <map>

#include "wifi.h"

#define MQTT_LED_ENABLED_TOPIC "led/enabled"
#define MQTT_MONIT_TEXT_TOPIC "monit/text"

#define PORT 1883

class Mqtt {
  public:
    static Mqtt &Instance();

    Mqtt();

    Mqtt(Mqtt const &) = delete;
    void operator=(Mqtt const &) = delete;

    void setup() {}
    void loop();

    String get(const String &topic);
    void set(const String &topic, const String &payload);

  private:
    static void callback(char *topic, byte *payload, unsigned int length);

    static constexpr char *m_mqtt_server = "192.168.2.254";

    WiFiClient m_espClient;
    PubSubClient m_client;
};

#endif
