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

static FPanel fpanel;
FPanel &FPanel::Instance()
{
    return fpanel;
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

void FPanel::loop()
{
    if (gpio_power_handler_val) {
        gpio_power_handler_val = false;
        togglePower();
    }

    if (gpio_acknowledge_handler_val) {
        gpio_acknowledge_handler_val = false;
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

    if (m_error_code == 0) {
        m_led_power_state = true;
        m_led_error_state = false;
    } else {
        m_led_power_state = !m_led_power_state;
        m_led_error_state = !m_led_error_state;
    }

    digitalWrite(GPIO_POWER_LED_PIN, m_led_power_state);
    digitalWrite(GPIO_ERROR_LED_PIN, m_led_error_state);
}

void FPanel::togglePower()
{
    if (!m_power.clicked())
        return;

    Led::Instance().setForceOff(m_power.val != 0);
    Display::Instance().setForceOff(m_power.val != 0);

    Serial.print(__func__);
    Serial.print(": ");
    Serial.println(m_power.val);
}

void FPanel::toggleAcknowledge()
{
    if (!m_acknowledge.clicked())
        return;

    Led::Instance().setSilenceError(m_acknowledge.val != 0);

    Serial.print(__func__);
    Serial.print(": ");
    Serial.println(m_acknowledge.val);
}

bool Button::clicked()
{
    unsigned long time = millis();
    if ((time - last_time) < 10000)
        return false;

    last_time = time;

    if (val != 0) { // time expired or was never set
        val = 0;    // remove handler
        return true;
    }
    val = Wifi::Instance().getEpochTime() + timeout * 60; // set new timeout
    return true;
}
