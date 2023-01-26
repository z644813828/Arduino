#include <Arduino.h>

#include "display.h"
#include "led.h"
#include "motion.h"

#define MOTION_PIN D4

Motion &Motion::Instance()
{
    static Motion instance;
    return instance;
}

void Motion::setup()
{
    pinMode(MOTION_PIN, INPUT);
    m_time = millis();
}

void Motion::set(bool data)
{
    if (m_data == data)
        return;

    Serial.print(__func__);
    Serial.println(data);
    m_data = data;
    Led::Instance().setForceShow(data);
    Display::Instance().setForceShow(data);
}

void Motion::loop()
{
    if (digitalRead(MOTION_PIN) == HIGH) {
        m_time = millis() + (m_timeout * 1000);
        set(true);
        return;
    }

    if (millis() < m_time)
        return;

    set(false);
}
