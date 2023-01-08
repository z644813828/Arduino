// https://kit.alexgyver.ru/tutorials/moisture/

#include <Arduino.h>

#include "display.h"
#include "soil_wetness.h"

#define DRY_SIGNAL 230

SoilWetness &SoilWetness::Instance()
{
    static SoilWetness instance;
    return instance;
}

void SoilWetness::loop()
{
    // Display::Instance().setSoilWetness(analogRead(0) < DRY_SIGNAL);
    Display::Instance().setSoilWetness(true);
}
