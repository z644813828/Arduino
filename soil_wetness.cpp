// https://kit.alexgyver.ru/tutorials/moisture/

#include <Arduino.h>

#include "display.h"
#include "soil_wetness.h"

SoilWetness &SoilWetness::Instance()
{
    static SoilWetness instance;
    return instance;
}

void SoilWetness::loop()
{
    // Display::Instance().setSoilWetness(analogRead(0) < m_dry_signal);
    Display::Instance().setSoilWetness(true);
    m_data = true;
}
