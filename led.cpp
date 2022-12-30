#include "unistd.h"
#include <chrono>
#include <iostream>

#include "led.hpp"
#include "mqtt.hpp"

#ifdef ARDUINO
#include "FastLED.h"
#else

class CRGB {
  public:
    enum Color { Off, Red, Green, White };

    void operator=(Color val) { m_value = val; }
    bool operator==(Color val) { return m_value == val; }

  private:
    Color m_value;
};

long int millis()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
#endif

#define LED_PIN 6
#define LED_NUM 12

static CRGB strip[LED_NUM];
static long int next_blink_time;

static int error_code = 0;

static CRGB::Color color = CRGB::Color::Red;

static void print()
{
    auto get_char = [](int i) {
        if (strip[i] == CRGB::Red)
            return 'R';
        if (strip[i] == CRGB::White)
            return 'W';
        return ' ';
    };

    for (int i = 0; i < LED_NUM; i++)
        printf("%c", get_char(i));
    printf("\n");
}

static void starry_night()
{
    for (int i = 0; i < LED_NUM; i++)
        strip[i] = color;

    if (millis() > next_blink_time) {
        int led_idx = rand() % LED_NUM;
        strip[led_idx] = CRGB::White;
        next_blink_time += rand() % 10000;
    }
}

static void led_error()
{
    if (millis() > next_blink_time) {
        CRGB::Color c = strip[0] == CRGB::Off ? color : CRGB::Off;

        printf("%s:%d \n", __func__, __LINE__); // DBGPRINT
        for (int i = 0; i < LED_NUM; i++)
            strip[i] = c;
        next_blink_time += 500;
    }
}

static void mqtt_handle()
{
    // FastLED.setBrightness(mqtt.brightness);
    color = CRGB::Color(color);
}

void led_setup()
{
    color = CRGB::Red;
    next_blink_time = millis();
    // FastLED.addLeds<WS2812, LED_NUM, GRB>(strip, LED_NUM);
    // FastLED.setBrightness(255);
}

void led_loop()
{

    mqtt_handle();

    if (error_code != 0)
        led_error();
    else
        starry_night();

    print();
    // FastLED.show();
}

void led_set_brightness(int b)
{
    (void)b;
    // FastLED.setBrightness(b);
}

void led_setup_color(std::string color)
{
    if (color == "Red") {
        color = CRGB::Color::Red;
    } else if (color == "Green") {
        color = CRGB::Color::Green;
    } else if (color == "Off") {
        color = CRGB::Color::Off;
    }
}

void led_set_error_code(int code)
{
    error_code = code;
}
