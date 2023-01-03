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

static SSD1306 display(0x3C, D2, D5); // Address set here 0x3C that I found in the scanner, and pins defined as D2
                                      // (SDA/Serial Data), and D5 (SCK/Serial Clock).

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

void display_setup()
{
    display.init();
    display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    // display.flipScreenVertically();

    next_update_time = millis();

    memset(&_monit, 0, sizeof(Status));
    memset(&_wifi, 0, sizeof(Status));
    memset(&_mqtt, 0, sizeof(Status));
    memset(&_soil_wetness, 0, sizeof(Status));
    memset(&_power, 0, sizeof(Status));
    memset(&_logo34, 0, sizeof(Status));
    memset(&_logo68, 0, sizeof(Status));

    // top navbar
    _wifi.x = 0;
    _wifi.y = 2;
    _wifi.img = Signal816;
    _wifi.width = 16;
    _wifi.height = 8;

    _mqtt.x = 24;
    _mqtt.y = 2;
    _mqtt.img = Bluetooth88;
    _mqtt.width = 8;
    _mqtt.height = 8;

    _monit.x = 64;
    _monit.y = 2;
    _monit.img = Msg816;
    _monit.width = 16;
    _monit.height = 8;

    _soil_wetness.x = 88;
    _soil_wetness.y = 2;
    _soil_wetness.img = epd_bitmap_leeve;
    _soil_wetness.width = 8;
    _soil_wetness.height = 8;

    _power.status = true;
    _power.x = 112;
    _power.y = 2;
    _power.img = Bat816;
    _power.width = 16;
    _power.height = 8;

    // main icon
    _logo68.status = true;
    _logo68.x = (WIDTH - 68) / 2;
    _logo68.y = (HEIGHT - 8) / 2;
    _logo68.img = epd_bitmap_rog;
    _logo68.width = 68;
    _logo68.height = 34;

    _logo34.x = (WIDTH - 34) / 2;
    _logo68.y = (HEIGHT - 8) / 2;
    _logo34.img = epd_bitmap_rog;
    _logo34.width = 34;
    _logo34.height = 34;
}

static void display_status(Status *s)
{
    if (s->status) {
        display.drawFastImage(s->x, s->y, s->width, s->height, s->img);
    } else {
        // convert (8*8 || 16*8) -> (34*34 || 68*34)
        Status *logo = s->width == 8 ? &_logo34 : &_logo68;

        display.drawFastImage(logo->x, logo->y, logo->width, logo->height, s->img);

        if (!s->text.isEmpty())
            display.drawString(WIDTH / 2, HEIGHT - 3, _monit.text);

        if (s->shown)
            display.drawFastImage(s->x, s->y, s->width, s->height, s->img);
        s->shown = !s->shown;
    }
}

void display_loop()
{
    if (millis() < next_update_time)
        return;

    next_update_time += 200;

    display.clear();

    display_status(&_logo68);
    display_status(&_wifi);
    display_status(&_mqtt);
    display_status(&_monit);
    display_status(&_power);

    display.display();
}

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
