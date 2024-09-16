// https://kit.alexgyver.ru/tutorials/moisture/

#include <Arduino.h>

#include "display.h"
#include "soil_wetness.h"

static SoilWetness soil_wetness;
SoilWetness &SoilWetness::Instance()
{
    return soil_wetness;
}

void SoilWetness::loop()
{
    // Display::Instance().setSoilWetness(analogRead(0) < m_dry_signal);
    Display::Instance().setSoilWetness(true);
    m_data = true;
}
