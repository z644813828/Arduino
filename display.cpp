// https://electropeak.com/learn/the-beginners-guide-to-display-text-image-animation-on-oled-display-by-arduino/
// https://www.instructables.com/How-to-Display-Images-on-OLED-Using-Arduino/
// https://blog.hau.me/2018/12/26/i2c-oled-display-on-a-wemos-d1-mini/
// https://www.instructables.com/Wemos-D1-Mini-096-SSD1306-OLED-Display-Using-SPI/

#include <Arduino.h>

#include <SSD1306.h>

#include "display.h"

#define WIDTH 128
#define HEIGHT 64
#define PAGES 8

static SSD1306 display(0x3C, D2, D5);

struct Status {
    bool shown;
    String text;
    bool status;

    uint8_t x;
    uint8_t y;
    const uint8_t *img;
    uint8_t width;
    uint8_t height;
};

static Status _monit;
static Status _wifi;
static Status _mqtt;
static Status _soil_wetness;
static Status _power;
static Status _logo34;
static Status _logo68;

static long int next_update_time;

void display_setup() {}

void display_loop() {}

void display_monit_text(String text)
{
    _monit.status = text.isEmpty();
    _monit.text = text;
}

void display_mqtt_connected(bool b)
{
    _mqtt.status = b;
}

void display_wifi_connected(bool b)
{
    _wifi.status = b;
}

void display_soil_wetness(bool b)
{
    _soil_wetness.status = b;
}
