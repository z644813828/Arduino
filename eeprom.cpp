#include <EEPROM.h>

#include "fpanel.h"
#include "display.h"
#include "eeprom.h"
#include "led.h"
#include "motion.h"
#include "soil_wetness.h"

void Eeprom::setup()
{
    EEPROM.begin(sizeof(Data));
}

void Eeprom::load()
{
    Data data;
    EEPROM.get(0, data);

    Serial.println("Eeprom::load");
    data.println();

    Led::Instance().setBrightness(data.brightness);
    Led::Instance().setColor(String(data.color));
    Led::Instance().setEffect(String(data.effect));
    Led::Instance().setErrorEffect(String(data.error_effect));

    for (int i = 0; i < 3; i++)
        Led::Instance().setEffectArg(i, data.effect_arg[i]);

    SoilWetness::Instance().setDrySignal(data.soil_wetness);

    Display::Instance().setBrightness(data.display_brightness);
    Display::Instance().setOffBrightness(data.display_off_brightness);

    Motion::Instance().setTimeout(data.motion_timeout);
    Motion::Instance().setTimeStart(data.motion_time_start);
    Motion::Instance().setTimeStop(data.motion_time_stop);
    Motion::Instance().setTimeStop(data.motion_time_stop);
    FPanel::Instance().setPowerTimeout(data.fpanel_power_timeout);
    FPanel::Instance().setAcknowledgeTimeout(data.fpanel_acknowledge_timeout);
}

void Eeprom::save()
{
    Data data;
    memset(&data, 0, sizeof(Data));

    data.brightness = Led::Instance().getBrightness();
    Led::Instance().getColor().toCharArray(data.color, ARG_LEN);
    Led::Instance().getEffect().toCharArray(data.effect, ARG_LEN);
    Led::Instance().getErrorEffect().toCharArray(data.error_effect, ARG_LEN);

    for (int i = 0; i < 3; i++)
        data.effect_arg[i] = Led::Instance().getEffectArg(i);

    data.soil_wetness = SoilWetness::Instance().getDrySignal();

    data.display_brightness = Display::Instance().getBrightness();
    data.display_off_brightness = Display::Instance().getOffBrightness();

    data.motion_timeout = Motion::Instance().getTimeout();
    data.motion_time_start = Motion::Instance().getTimeStart();
    data.motion_time_stop = Motion::Instance().getTimeStop();

    data.fpanel_power_timeout = FPanel::Instance().getPowerTimeout();
    data.fpanel_acknowledge_timeout = FPanel::Instance().getAcknowledgeTimeout();

    Serial.println("Eeprom::save");
    data.println();

    EEPROM.put(0, data);
    EEPROM.commit();
}
