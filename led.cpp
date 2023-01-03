// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/

// #define FASTLED_ALL_PINS_HARDWARE_SPI
// #define FASTLED_ESP8266_RAW_PIN_ORDER
// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
// #define FASTLED_ESP8266_D1_PIN_ORDER

#include <FastLED.h>

#define LED_PIN 5
#define LED_NUM 120

static CRGB strip[LED_NUM];
static long int next_blink_time;

static int error_code = 0;
static int brightness = 255;
static bool enabled = true;

static CRGB color = CRGB::Red;

static bool starry_night()
{
    for (int i = 0; i < LED_NUM; ++i)
        strip[i] = color;

    static long int unset_time;

    if (unset_time) {
        unset_time = 0;
        return true;
    }

    if (millis() < next_blink_time)
        return false;

    unset_time = millis() + 50;

    for (int i = 0; i < 10; ++i)
        strip[rand() % LED_NUM] = CRGB::White;

    next_blink_time += rand() % 10000;

    return true;
}

static bool led_error()
{
    if (millis() < next_blink_time)
        return false;

    FastLED.setBrightness((FastLED.getBrightness() == brightness) ? 0 : brightness);
    FastLED.show();

    next_blink_time += 500;

    return true;
}

void led_setup()
{
    color = CRGB::Red;
    next_blink_time = millis();
    FastLED.addLeds<WS2812, LED_PIN, GRB>(strip, LED_NUM);
    FastLED.setBrightness(255);
}

void led_loop()
{
    if (!enabled)
        return;

    if (error_code != 0) {
        if (!led_error())
            return;
    } else {
        if (!starry_night())
            return;
    }

    FastLED.show();
}

void led_set_brightness(int b)
{
    (void)b;
    FastLED.setBrightness(b);
    brightness = b;
    FastLED.show();
}
void led_set_error_code(int code)
{
    error_code = code;
}

void led_set_enabled(bool e)
{
    enabled = e;
    FastLED.setBrightness(e ? brightness : 0);
    FastLED.show();
}

void led_set_color(String color)
{
    // clang-format off
         if (color == "Amethyst") color = CRGB::Amethyst;
    else if (color == "AntiqueWhite") color = CRGB::AntiqueWhite;
    else if (color == "Aqua") color = CRGB::Aqua;
    else if (color == "Aquamarine") color = CRGB::Aquamarine;
    else if (color == "Azure") color = CRGB::Azure;
    else if (color == "Beige") color = CRGB::Beige;
    else if (color == "Bisque") color = CRGB::Bisque;
    else if (color == "Black") color = CRGB::Black;
    else if (color == "BlanchedAlmond") color = CRGB::BlanchedAlmond;
    else if (color == "Blue") color = CRGB::Blue;
    else if (color == "BlueViolet") color = CRGB::BlueViolet;
    else if (color == "Brown") color = CRGB::Brown;
    else if (color == "BurlyWood") color = CRGB::BurlyWood;
    else if (color == "CadetBlue") color = CRGB::CadetBlue;
    else if (color == "Chartreuse") color = CRGB::Chartreuse;
    else if (color == "Chocolate") color = CRGB::Chocolate;
    else if (color == "Coral") color = CRGB::Coral;
    else if (color == "CornflowerBlue") color = CRGB::CornflowerBlue;
    else if (color == "Cornsilk") color = CRGB::Cornsilk;
    else if (color == "Crimson") color = CRGB::Crimson;
    else if (color == "Cyan") color = CRGB::Cyan;
    else if (color == "DarkBlue") color = CRGB::DarkBlue;
    else if (color == "DarkCyan") color = CRGB::DarkCyan;
    else if (color == "DarkGoldenrod") color = CRGB::DarkGoldenrod;
    else if (color == "DarkGray") color = CRGB::DarkGray;
    else if (color == "DarkGrey") color = CRGB::DarkGrey;
    else if (color == "DarkGreen") color = CRGB::DarkGreen;
    else if (color == "DarkKhaki") color = CRGB::DarkKhaki;
    else if (color == "DarkMagenta") color = CRGB::DarkMagenta;
    else if (color == "DarkOliveGreen") color = CRGB::DarkOliveGreen;
    else if (color == "DarkOrange") color = CRGB::DarkOrange;
    else if (color == "DarkOrchid") color = CRGB::DarkOrchid;
    else if (color == "DarkRed") color = CRGB::DarkRed;
    else if (color == "DarkSalmon") color = CRGB::DarkSalmon;
    else if (color == "DarkSeaGreen") color = CRGB::DarkSeaGreen;
    else if (color == "DarkSlateBlue") color = CRGB::DarkSlateBlue;
    else if (color == "DarkSlateGray") color = CRGB::DarkSlateGray;
    else if (color == "DarkSlateGrey") color = CRGB::DarkSlateGrey;
    else if (color == "DarkTurquoise") color = CRGB::DarkTurquoise;
    else if (color == "DarkViolet") color = CRGB::DarkViolet;
    else if (color == "DeepPink") color = CRGB::DeepPink;
    else if (color == "DeepSkyBlue") color = CRGB::DeepSkyBlue;
    else if (color == "DimGray") color = CRGB::DimGray;
    else if (color == "DimGrey") color = CRGB::DimGrey;
    else if (color == "DodgerBlue") color = CRGB::DodgerBlue;
    else if (color == "FireBrick") color = CRGB::FireBrick;
    else if (color == "FloralWhite") color = CRGB::FloralWhite;
    else if (color == "ForestGreen") color = CRGB::ForestGreen;
    else if (color == "Fuchsia") color = CRGB::Fuchsia;
    else if (color == "Gainsboro") color = CRGB::Gainsboro;
    else if (color == "GhostWhite") color = CRGB::GhostWhite;
    else if (color == "Gold") color = CRGB::Gold;
    else if (color == "Goldenrod") color = CRGB::Goldenrod;
    else if (color == "Gray") color = CRGB::Gray;
    else if (color == "Grey") color = CRGB::Grey;
    else if (color == "Green") color = CRGB::Green;
    else if (color == "GreenYellow") color = CRGB::GreenYellow;
    else if (color == "Honeydew") color = CRGB::Honeydew;
    else if (color == "HotPink") color = CRGB::HotPink;
    else if (color == "IndianRed") color = CRGB::IndianRed;
    else if (color == "Indigo") color = CRGB::Indigo;
    else if (color == "Ivory") color = CRGB::Ivory;
    else if (color == "Khaki") color = CRGB::Khaki;
    else if (color == "Lavender") color = CRGB::Lavender;
    else if (color == "LavenderBlush") color = CRGB::LavenderBlush;
    else if (color == "LawnGreen") color = CRGB::LawnGreen;
    else if (color == "LemonChiffon") color = CRGB::LemonChiffon;
    else if (color == "LightBlue") color = CRGB::LightBlue;
    else if (color == "LightCoral") color = CRGB::LightCoral;
    else if (color == "LightCyan") color = CRGB::LightCyan;
    else if (color == "LightGoldenrodYellow") color = CRGB::LightGoldenrodYellow;
    else if (color == "LightGreen") color = CRGB::LightGreen;
    else if (color == "LightGrey") color = CRGB::LightGrey;
    else if (color == "LightPink") color = CRGB::LightPink;
    else if (color == "LightSalmon") color = CRGB::LightSalmon;
    else if (color == "LightSeaGreen") color = CRGB::LightSeaGreen;
    else if (color == "LightSkyBlue") color = CRGB::LightSkyBlue;
    else if (color == "LightSlateGray") color = CRGB::LightSlateGray;
    else if (color == "LightSlateGrey") color = CRGB::LightSlateGrey;
    else if (color == "LightSteelBlue") color = CRGB::LightSteelBlue;
    else if (color == "LightYellow") color = CRGB::LightYellow;
    else if (color == "Lime") color = CRGB::Lime;
    else if (color == "LimeGreen") color = CRGB::LimeGreen;
    else if (color == "Linen") color = CRGB::Linen;
    else if (color == "Magenta") color = CRGB::Magenta;
    else if (color == "Maroon") color = CRGB::Maroon;
    else if (color == "MediumAquamarine") color = CRGB::MediumAquamarine;
    else if (color == "MediumBlue") color = CRGB::MediumBlue;
    else if (color == "MediumOrchid") color = CRGB::MediumOrchid;
    else if (color == "MediumPurple") color = CRGB::MediumPurple;
    else if (color == "MediumSeaGreen") color = CRGB::MediumSeaGreen;
    else if (color == "MediumSlateBlue") color = CRGB::MediumSlateBlue;
    else if (color == "MediumSpringGreen") color = CRGB::MediumSpringGreen;
    else if (color == "MediumTurquoise") color = CRGB::MediumTurquoise;
    else if (color == "MediumVioletRed") color = CRGB::MediumVioletRed;
    else if (color == "MidnightBlue") color = CRGB::MidnightBlue;
    else if (color == "MintCream") color = CRGB::MintCream;
    else if (color == "MistyRose") color = CRGB::MistyRose;
    else if (color == "Moccasin") color = CRGB::Moccasin;
    else if (color == "NavajoWhite") color = CRGB::NavajoWhite;
    else if (color == "Navy") color = CRGB::Navy;
    else if (color == "OldLace") color = CRGB::OldLace;
    else if (color == "Olive") color = CRGB::Olive;
    else if (color == "OliveDrab") color = CRGB::OliveDrab;
    else if (color == "Orange") color = CRGB::Orange;
    else if (color == "OrangeRed") color = CRGB::OrangeRed;
    else if (color == "Orchid") color = CRGB::Orchid;
    else if (color == "PaleGoldenrod") color = CRGB::PaleGoldenrod;
    else if (color == "PaleGreen") color = CRGB::PaleGreen;
    else if (color == "PaleTurquoise") color = CRGB::PaleTurquoise;
    else if (color == "PaleVioletRed") color = CRGB::PaleVioletRed;
    else if (color == "PapayaWhip") color = CRGB::PapayaWhip;
    else if (color == "PeachPuff") color = CRGB::PeachPuff;
    else if (color == "Peru") color = CRGB::Peru;
    else if (color == "Pink") color = CRGB::Pink;
    else if (color == "Plaid") color = CRGB::Plaid;
    else if (color == "Plum") color = CRGB::Plum;
    else if (color == "PowderBlue") color = CRGB::PowderBlue;
    else if (color == "Purple") color = CRGB::Purple;
    else if (color == "Red") color = CRGB::Red;
    else if (color == "RosyBrown") color = CRGB::RosyBrown;
    else if (color == "RoyalBlue") color = CRGB::RoyalBlue;
    else if (color == "SaddleBrown") color = CRGB::SaddleBrown;
    else if (color == "Salmon") color = CRGB::Salmon;
    else if (color == "SandyBrown") color = CRGB::SandyBrown;
    else if (color == "SeaGreen") color = CRGB::SeaGreen;
    else if (color == "Seashell") color = CRGB::Seashell;
    else if (color == "Sienna") color = CRGB::Sienna;
    else if (color == "Silver") color = CRGB::Silver;
    else if (color == "SkyBlue") color = CRGB::SkyBlue;
    else if (color == "SlateBlue") color = CRGB::SlateBlue;
    else if (color == "SlateGray") color = CRGB::SlateGray;
    else if (color == "SlateGrey") color = CRGB::SlateGrey;
    else if (color == "Snow") color = CRGB::Snow;
    else if (color == "SpringGreen") color = CRGB::SpringGreen;
    else if (color == "SteelBlue") color = CRGB::SteelBlue;
    else if (color == "Tan") color = CRGB::Tan;
    else if (color == "Teal") color = CRGB::Teal;
    else if (color == "Thistle") color = CRGB::Thistle;
    else if (color == "Tomato") color = CRGB::Tomato;
    else if (color == "Turquoise") color = CRGB::Turquoise;
    else if (color == "Violet") color = CRGB::Violet;
    else if (color == "Wheat") color = CRGB::Wheat;
    else if (color == "White") color = CRGB::White;
    else if (color == "WhiteSmoke") color = CRGB::WhiteSmoke;
    else if (color == "Yellow") color = CRGB::Yellow;
    else if (color == "YellowGreen") color = CRGB::YellowGreen;
    // clang-format on
}
