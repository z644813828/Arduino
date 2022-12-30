#include "unistd.h"

#include "display.hpp"
#include "led.hpp"
#include "mqtt.hpp"

void setup()
{
    mqtt_setup();
    led_setup();
    display_setup();
}

void loop()
{
    mqtt_loop();
    led_loop();
    display_loop();
}

#ifndef ARDUINO
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    setup();

    while (1) {
        loop();
        usleep(1000 * 10);
    }

    return 0;
}
#endif
