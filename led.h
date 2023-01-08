#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>
#include <map>

#define LED_PIN D3
#define LED_NUM 80

class Led {
  public:
    static Led &Instance();

    Led() {}

    Led(Led const &) = delete;
    void operator=(Led const &) = delete;

    void setup();
    void loop();

    void setBrightness(int b);

    void setColor(String color);
    String getColor();

    void setErrorCode(int code);

    void setEnabled(bool enabled);

    String getHtmlColors();

  private:
    void starry_night();
    void led_error();
    void fill_color_map();

    CRGB m_strip[LED_NUM];
    long int m_next_blink_time;

    int m_error_code = 0;
    int m_brightness = 255;
    bool m_enabled = true;

    CRGB m_color = CRGB::Red;
    String m_color_str = "Red";
    std::map<String, CRGB> m_color_map;
};

#endif
