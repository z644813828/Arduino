#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>
#include <map>

#define LED_PIN D3
#define LED_NUM 80
#define NUM_LEDS LED_NUM

// clang-format off
#define DEBUG \
    Serial.print(__func__); \
    Serial.print(":"); \
    Serial.println(__LINE__); \
    delay(5000);
// clang-format on

class Led {
  public:
    static Led &Instance();

    Led() {}

    Led(Led const &) = delete;
    void operator=(Led const &) = delete;

    void setup();
    void loop();

    void setBrightness(int b);
    int getBrightness() { return m_brightness; }

    void setColor(String color);
    void setEffect(String color);
    void setErrorEffect(String color);
    void setEffectArg(int idx, String arg);

    void setErrorCode(int code);

    void setEnabled(bool enabled);

    void setDebug(bool d) { m_debug = d; }
    bool getDebug() { return m_debug; };

    String getHtmlColors();
    String getHtmlEffects();
    String getHtmlErrorEffects();
    String getHtmlArguments();

  private:
    // functions to interact with strip
    void setPixel(int Pixel, byte red, byte green, byte blue);
    void setAll(byte red, byte green, byte blue);
    void showStrip();
    String getHtmlEffectsP(const String &color);

    // effects
    void StarryNight();
    void BouncingColoredBalls();
    void BouncingBalls();
    void ColorWipe();
    void CylonBounce();
    void FadeInOut();
    void Fire();
    void HalloweenEyes();
    void NewKITT();
    void RainbowCycle();
    void TwinkleRandom();
    void RunningLights();
    void SnowSparkle();
    void Sparkle();
    void Strobe();
    void TheaterChaseRainbow();
    void TheaterChase();
    void Twinkle();

    void fillColorMap();
    void fillEffectsMap();

    CRGB m_strip[LED_NUM];

    int m_error_code = 0;
    int m_brightness = 255;
    bool m_enabled = true;
    bool m_debug = false;

    CRGB m_color = CRGB::Red;
    String m_color_str = "Red";
    String m_effect = "BouncingBalls";
    String m_error_effect = "BouncingBalls";

    std::map<String, CRGB> m_color_map;
    std::map<String, std::map<String, int>> m_effect_map;
};

#endif
