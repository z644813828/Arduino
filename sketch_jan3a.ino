#include "led.h"
#include "mqtt.h"

void setup()
{
    Serial.begin(115200);
    delay(10);

    // mqtt_setup();
    Led::Instance().setup();
}

void loop()
{
    // mqtt_loop();
    Led::Instance().loop();
}
