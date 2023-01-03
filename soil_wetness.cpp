// https://kit.alexgyver.ru/tutorials/moisture/

#include <Arduino.h>

#include "display.h"

#define DRY_SIGNAL 230

void soil_wetness_setup() {}

static bool g_status = false;

void soil_wetness_loop()
{
    display_soil_wetness(analogRead(0) < DRY_SIGNAL);
}
