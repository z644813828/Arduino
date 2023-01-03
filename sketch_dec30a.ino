#include "display.h"
#include "led.h"
#include "mqtt.h"
#include "soil_wetness.h"

void setup()
{
    Serial.begin(115200);
    mqtt_setup();
    led_setup();
    display_setup();
    soil_wetness_setup();
}

void loop()
{
    mqtt_loop();
    led_loop();
    display_loop();
    soil_wetness_loop();
}
