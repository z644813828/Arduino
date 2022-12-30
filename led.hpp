#ifndef LED_H
#define LED_H

#include <string>

void led_setup();
void led_loop();

void led_set_brightness(int b);
void led_set_color(std::string color);
void led_set_error_code(int code);

#endif
