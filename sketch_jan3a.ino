#include "display.h"
#include "led.h"
#include "mqtt.h"
#include "soil_wetness.h"
#include "wifi.h"

#define VERSION "1.0.0"

void setup()
{
    Serial.begin(115200);

    delay(2000);

    Serial.println("");
    Serial.print(VERSION);
    Serial.println(" started with debug");

    Led::Instance().setup();
    // Display::Instance().setup();
    // SoilWetness::Instance().setup();
    Wifi::Instance().setup();
    // Mqtt::Instance().setup();
}

void loop()
{
    Led::Instance().loop();
    // Display::Instance().loop();
    // SoilWetness::Instance().loop();
    Wifi::Instance().loop();
    // Mqtt::Instance().loop();
}
