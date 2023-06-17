#include "fpanel.h"
#include "display.h"
#include "led.h"
#include "mqtt.h"

Mqtt::Mqtt()
    : m_client(m_espClient)
{
}

Mqtt &Mqtt::Instance()
{
    static Mqtt instance;
    return instance;
}

static std::map<String, String> m_data;

void Mqtt::callback(char *topic, byte *payload, unsigned int length)
{
    payload[length] = '\0';
    String str_topic = String(topic);
    String str_payload = String((char *)payload);
    str_payload.replace("\n", " ");

    auto it = m_data.find(str_topic);
    if (it != m_data.end()) {
        if (it->second == str_payload)
            return;
        m_data.erase(it);
    }

    m_data.insert(std::pair<String, String>(str_topic, str_payload));

    Serial.print(topic);
    Serial.print("  ");
    Serial.println(str_payload);

    if (str_topic == MQTT_MONIT_TEXT_TOPIC) {
        Display::Instance().setMonitText(str_payload);
        Led::Instance().setErrorCode(!str_payload.isEmpty());
        FPanel::Instance().setErrorCode(!str_payload.isEmpty());
    } else if (str_topic == MQTT_LED_ENABLED_TOPIC) {
        Led::Instance().setEnabled(str_payload.toInt());
        Display::Instance().setEnabled(str_payload.toInt());
    }
}

void Mqtt::loop()
{
    if (!Wifi::Instance().getStatus())
        return;

    if (m_client.connected()) {
        Display::Instance().setMqttConnected(true);
        m_client.loop();
        return;
    }

    m_client.setServer(m_mqtt_server, PORT);
    m_client.setCallback(callback);

    Display::Instance().setMqttConnected(false);

    String clientId = "ESP32Client";

    if (!m_client.connect(clientId.c_str()))
        return;

    Serial.println("MQTT connected");
    m_client.subscribe(MQTT_LED_ENABLED_TOPIC);
    m_client.subscribe(MQTT_MONIT_TEXT_TOPIC);
}

String Mqtt::get(const String &topic)
{
    auto it = m_data.find(topic);
    if (it == m_data.end())
        return String();
    return (it->second);
}

void Mqtt::set(const String &topic, const String &payload)
{
    m_data.insert(std::pair<String, String>(topic, payload));
    m_client.publish(topic.c_str(), payload.c_str());
}
