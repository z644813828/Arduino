#ifndef LED_H
#define LED_H

#include <Arduino.h>

void led_setup();
void led_loop();

void led_set_brightness(int b);
void led_set_color(String color);
void led_set_error_code(int code);

void led_set_enabled(bool enabled);

#endif
