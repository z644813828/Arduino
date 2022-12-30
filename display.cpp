#include <iostream>

#include "display.hpp"
#include "mqtt.hpp"

static std::string text;

void display_setup() {}

void display_loop() {}

void display_set_text(std::string text)
{
    std::cout << __func__ << " " << text << std::endl;
}
