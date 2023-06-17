#include <Arduino.h>

#include "config.h"
#include "display.h"
#include "led.h"
#include "motion.h"
#include "wifi.h"

Motion &Motion::Instance()
{
    static Motion instance;
    return instance;
}

void Motion::setup()
{
    pinMode(GPIO_MOTION_PIN, INPUT);
    m_time = millis();
}

void Motion::set(bool data)
{
    if (m_data == data)
        return;

    Serial.print("Motion: ");
    Serial.println(data);
    m_data = data;

    Led::Instance().setForceOn(data);
    Display::Instance().setForceOn(data);
}

void Motion::loop()
{
    auto is_time_allowed = [&]() {
        int time = Wifi::Instance().getTime();

        if (time == -1)
            return true;

        if (m_time_stop > m_time_start)
            return ((time >= m_time_start) && (time <= m_time_stop));

        return !((time <= m_time_start) && (time >= m_time_stop));
    };

    if (digitalRead(GPIO_MOTION_PIN) == HIGH) {
        m_time = millis() + (m_timeout * 1000);

        if (!is_time_allowed())
            return;

        set(true);
        return;
    }

    if (millis() < m_time)
        return;

    set(false);
}
