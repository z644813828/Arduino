#include "display.h"
#include "eeprom.h"
#include "fpanel.h"
#include "led.h"
#include "motion.h"
#include "mqtt.h"
#include "soil_wetness.h"
#include "wifi.h"

#include "secrets.h"

Wifi::Wifi()
    : m_server(80)
    , m_timeClient(m_ntpUDP, "pool.ntp.org", m_utcOffsetInSeconds)
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

#ifdef SCAN_WIFI
    for (int i = 0; i < WiFi.scanNetworks(); i++)
        Serial.println(WiFi.SSID(i));

    delay(2000);
#endif

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.hostname("Name");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void Wifi::InitHandler()
{
    m_server.on("/settings", [&]() {
        // clang-format off
        String str = R"(
            {
                "brightness": )" + String(Led::Instance().getBrightness()) + R"(,
                "effects": [
                    )" + Led::Instance().getEffects() + R"(
                ],
                "colors": [
                    )" + Led::Instance().getColors() + R"(
                ],
                "current_effect": ")" + Led::Instance().getEffect() + R"(",
                "current_error_effect": ")" + Led::Instance().getErrorEffect() + R"(",
                "current_color": ")" + Led::Instance().getColor() + R"(",
                "arguments": {
                    )" + Led::Instance().getArguments() + R"(
                },
                "debug_led": )" + String(Led::Instance().getDebug()) + R"(,
                "soil_wetness": )" + String(SoilWetness::Instance().getDrySignal()) + R"(,
                "motion_timeout": )" + String(Motion::Instance().getTimeout()) + R"(,
                "display_brightness": )" + String(Display::Instance().getBrightness()) + R"(,
                "display_off_brightness": )" + String(Display::Instance().getOffBrightness()) + R"(,
                "motion_time_start": )" + String(Motion::Instance().getTimeStart()) + R"(,
                "motion_time_stop": )" + String(Motion::Instance().getTimeStop()) + R"(,
                "fpanel_power_timeout" : )" + String(FPanel::Instance().getPowerTimeout()) + R"(,
                "fpanel_acknowledge_timeout" : )" + String(FPanel::Instance().getAcknowledgeTimeout()) + R"(
            }
        )";
        // clang-format on
        m_server.send(200, "text/html", str);
    });

    m_server.on("/data", [&]() {
        // clang-format off
        String str = R"(
            {
                "soil_wetness": )" + String(SoilWetness::Instance().getData()) + R"(,
                "motion": )" + String(Motion::Instance().getData()) + R"(,
                "power": )" + String(FPanel::Instance().getPower()) + R"(,
                "acknowledge": )" + String(FPanel::Instance().getAcknowledge()) + R"(
            }
        )";
        // clang-format on
        m_server.send(200, "text/html", str);
    });

    m_server.on("/save_eeprom", [&]() {
        String str = String(sizeof(Eeprom::Data));
        Eeprom::save();
        m_server.send(200, "text/html", str);
    });

    m_server.on("/reboot", [&]() {
        ESP.restart();
        m_server.send(200, "text/html", "OK");
    });

    m_server.on("/get", [&]() {
        String arg;
        String args_list = "";

        auto ARG = [&](String arg_name, const auto &cb) {
            if ((arg = m_server.arg(arg_name)) != "") {
                cb();
                args_list += ";";
                args_list += arg;
            }
        };

        // clang-format off
        ARG(HTTP_REQUEST_COLOR,                     [&]() { Led::Instance().setColor(arg); });
        ARG(HTTP_REQUEST_EFFECT,                    [&]() { Led::Instance().setEffect(arg); });
        ARG(HTTP_REQUEST_ERROR_EFFECT,              [&]() { Led::Instance().setErrorEffect(arg); });
        ARG(HTTP_REQUEST_BRIGHTNESS,                [&]() { Led::Instance().setBrightness(arg.toInt()); });
        ARG(HTTP_REQUEST_LED_DEBUG,                 [&]() { Led::Instance().setDebug(arg.toInt()); });

        ARG(HTTP_REQUEST_SOIL_WETNESS,              [&]() { SoilWetness::Instance().setDrySignal(arg.toInt()); });

        ARG(HTTP_REQUEST_MOTION_TIMEOUT,            [&]() { Motion::Instance().setTimeout(arg.toInt()); });
        ARG(HTTP_REQUEST_MOTION_TIME_START,         [&]() { Motion::Instance().setTimeStart(arg.toInt()); });
        ARG(HTTP_REQUEST_MOTION_TIME_STOP,          [&]() { Motion::Instance().setTimeStop(arg.toInt()); });

        ARG(HTTP_REQUEST_DISPLAY_TEST,              [&]() { Display::Instance().startSelfTest(); });
        ARG(HTTP_REQUEST_DISPLAY_BRIGHTNESS,        [&]() { Display::Instance().setBrightness(arg.toInt()); });
        ARG(HTTP_REQUEST_DISPLAY_OFF_BRIGHTNESS,    [&]() { Display::Instance().setOffBrightness(arg.toInt()); });

        ARG(HTTP_REQUEST_FPANEL_POWER,              [&]() { FPanel::Instance().togglePower(); });
        ARG(HTTP_REQUEST_FPANEL_ACKNOWLEDGE,        [&]() { FPanel::Instance().toggleAcknowledge(); });
        // clang-format on

        for (int i = 0; i < 10; i++) {
            String param = HTTP_REQUEST_EFFECT_ARG + String(i);
            ARG(param, [&, i]() { Led::Instance().setEffectArg(i, arg.toInt()); });
        }

        m_server.send(200, "text/html", args_list);
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
            m_timeClient.begin();
        } else {
            Serial.println("WiFi Disconnected");
        }
    }

    m_wifiStatus = new_status;
    Display::Instance().setWifiConnected(m_wifiStatus);

    m_server.handleClient();
    m_timeClient.update();
}

int Wifi::getTime()
{
    if (!m_wifiStatus)
        return -1;

    return (m_timeClient.getHours() + 3) * 60 + m_timeClient.getMinutes();
}

unsigned long Wifi::getEpochTime()
{
    return m_timeClient.getEpochTime();
}
