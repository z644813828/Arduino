#include <Arduino.h>

#include "config.h"
#include "display.h"
#include "fpanel.h"
#include "led.h"
#include "wifi.h"

static volatile bool gpio_power_handler_val = false;
static void ICACHE_RAM_ATTR gpio_power_handler()
{
    gpio_power_handler_val = true;
}

static volatile bool gpio_acknowledge_handler_val = false;
static void ICACHE_RAM_ATTR gpio_acknowledge_handler()
{
    gpio_acknowledge_handler_val = true;
}

FPanel &FPanel::Instance()
{
    static FPanel instance;
    return instance;
}

void FPanel::setup()
{
    pinMode(GPIO_POWER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(GPIO_ACKNOWLEDGE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(GPIO_POWER_LED_PIN, OUTPUT);
    pinMode(GPIO_ERROR_LED_PIN, OUTPUT);

    m_next_update_time = millis();

    attachInterrupt(digitalPinToInterrupt(GPIO_POWER_BUTTON_PIN), gpio_power_handler, RISING);
    attachInterrupt(digitalPinToInterrupt(GPIO_ACKNOWLEDGE_BUTTON_PIN), gpio_acknowledge_handler, RISING);
}

bool FPanel::checkTime(Button &btn)
{
    unsigned long time = millis();
    if ((time - btn.last_time) < 1000)
        return false;

    btn.last_time = time;
    return true;
}

void FPanel::loop()
{
    if (gpio_power_handler_val) {
        gpio_power_handler_val = false;
        if (checkTime(m_power))
            togglePower();
    }

    if (gpio_acknowledge_handler_val) {
        gpio_acknowledge_handler_val = false;
        if (checkTime(m_acknowledge))
            toggleAcknowledge();
    }

    unsigned long time = Wifi::Instance().getEpochTime();

    if (m_power.val && (time > m_power.val))
        togglePower();

    if (m_acknowledge.val && (time > m_acknowledge.val))
        toggleAcknowledge();

    if (millis() < m_next_update_time)
        return;

    m_next_update_time += 200;

    m_led_power_state = !m_led_power_state;

    if (m_error_code = 0)
        m_led_error_state = 0;
    else
        m_led_error_state = !m_led_error_state;

    digitalWrite(GPIO_POWER_LED_PIN, m_led_power_state);
    digitalWrite(GPIO_ERROR_LED_PIN, m_led_power_state);
}

static int toggle(int val, unsigned long timeout)
{
    return (val == 0)                                             // time expired or was never set
               ? (Wifi::Instance().getEpochTime() + timeout * 60) // set new timeout
               : 0;                                               // remove handler
}

void FPanel::togglePower()
{
    Serial.println(__func__);

    m_power.val = toggle(m_power.val, m_power.timeout);

    Led::Instance().setForceOff(m_power.val != 0);
    Display::Instance().setForceOff(m_power.val != 0);
}

void FPanel::toggleAcknowledge()
{
    Serial.println(__func__);

    m_acknowledge.val = toggle(m_acknowledge.val, m_acknowledge.timeout);

    Led::Instance().setSilenceError(m_acknowledge.val != 0);
}
