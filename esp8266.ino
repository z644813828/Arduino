#include "config.h"
#include "display.h"
#include "eeprom.h"
#include "fpanel.h"
#include "led.h"
#include "motion.h"
#include "mqtt.h"
#include "soil_wetness.h"
#include "wifi.h"

void setup()
{
    Serial.begin(115200);

    Serial.println("");
    Serial.print(VERSION);
    Serial.println(" started with debug");

    Led::Instance().setup();
    Display::Instance().setup();
    SoilWetness::Instance().setup();
    Wifi::Instance().setup();
    Mqtt::Instance().setup();
    Motion::Instance().setup();
    FPanel::Instance().setup();

    Eeprom::setup();
    Eeprom::load();

    delay(2000);
}

void loop()
{
    Led::Instance().loop();
    Display::Instance().loop();
    SoilWetness::Instance().loop();
    Wifi::Instance().loop();
    Mqtt::Instance().loop();
    Motion::Instance().loop();
    FPanel::Instance().loop();
}
