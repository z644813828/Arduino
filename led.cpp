// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/

// #define FASTLED_ALL_PINS_HARDWARE_SPI
// #define FASTLED_ESP8266_RAW_PIN_ORDER
// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
// #define FASTLED_ESP8266_D1_PIN_ORDER

#include "led.h"

Led &Led::Instance()
{
    static Led instance;
    return instance;
}

void Led::starry_night()
{
    for (int i = 0; i < LED_NUM; ++i)
        m_strip[i] = m_color;

    static long int unset_time = 0;

    if (unset_time) {
        unset_time = 0;
        FastLED.show();
        return;
    }

    if (millis() < m_next_blink_time)
        return;

    unset_time = millis() + 50;

    for (int i = 0; i < LED_NUM / 10; ++i)
        m_strip[rand() % LED_NUM] = CRGB::White;

    m_next_blink_time += rand() % 10000;

    int step = 100;
    int b = FastLED.getBrightness() - step + rand() % step;
    FastLED.setBrightness(b);
    FastLED.show();

    return;
}

void Led::led_error()
{
    if (millis() < m_next_blink_time)
        return;

    FastLED.setBrightness((FastLED.getBrightness() == m_brightness) ? 0 : m_brightness);
    FastLED.show();

    m_next_blink_time += 500;
}

void Led::fill_color_map()
{
    m_color_map.insert(std::pair<String, CRGB>("Amethyst", CRGB::Amethyst));
    m_color_map.insert(std::pair<String, CRGB>("AntiqueWhite", CRGB::AntiqueWhite));
    m_color_map.insert(std::pair<String, CRGB>("Aqua", CRGB::Aqua));
    m_color_map.insert(std::pair<String, CRGB>("Aquamarine", CRGB::Aquamarine));
    m_color_map.insert(std::pair<String, CRGB>("Azure", CRGB::Azure));
    m_color_map.insert(std::pair<String, CRGB>("Beige", CRGB::Beige));
    m_color_map.insert(std::pair<String, CRGB>("Bisque", CRGB::Bisque));
    m_color_map.insert(std::pair<String, CRGB>("Black", CRGB::Black));
    m_color_map.insert(std::pair<String, CRGB>("BlanchedAlmond", CRGB::BlanchedAlmond));
    m_color_map.insert(std::pair<String, CRGB>("Blue", CRGB::Blue));
    m_color_map.insert(std::pair<String, CRGB>("BlueViolet", CRGB::BlueViolet));
    m_color_map.insert(std::pair<String, CRGB>("Brown", CRGB::Brown));
    m_color_map.insert(std::pair<String, CRGB>("BurlyWood", CRGB::BurlyWood));
    m_color_map.insert(std::pair<String, CRGB>("CadetBlue", CRGB::CadetBlue));
    m_color_map.insert(std::pair<String, CRGB>("Chartreuse", CRGB::Chartreuse));
    m_color_map.insert(std::pair<String, CRGB>("Chocolate", CRGB::Chocolate));
    m_color_map.insert(std::pair<String, CRGB>("Coral", CRGB::Coral));
    m_color_map.insert(std::pair<String, CRGB>("CornflowerBlue", CRGB::CornflowerBlue));
    m_color_map.insert(std::pair<String, CRGB>("Cornsilk", CRGB::Cornsilk));
    m_color_map.insert(std::pair<String, CRGB>("Crimson", CRGB::Crimson));
    m_color_map.insert(std::pair<String, CRGB>("Cyan", CRGB::Cyan));
    m_color_map.insert(std::pair<String, CRGB>("DarkBlue", CRGB::DarkBlue));
    m_color_map.insert(std::pair<String, CRGB>("DarkCyan", CRGB::DarkCyan));
    m_color_map.insert(std::pair<String, CRGB>("DarkGoldenrod", CRGB::DarkGoldenrod));
    m_color_map.insert(std::pair<String, CRGB>("DarkGray", CRGB::DarkGray));
    m_color_map.insert(std::pair<String, CRGB>("DarkGrey", CRGB::DarkGrey));
    m_color_map.insert(std::pair<String, CRGB>("DarkGreen", CRGB::DarkGreen));
    m_color_map.insert(std::pair<String, CRGB>("DarkKhaki", CRGB::DarkKhaki));
    m_color_map.insert(std::pair<String, CRGB>("DarkMagenta", CRGB::DarkMagenta));
    m_color_map.insert(std::pair<String, CRGB>("DarkOliveGreen", CRGB::DarkOliveGreen));
    m_color_map.insert(std::pair<String, CRGB>("DarkOrange", CRGB::DarkOrange));
    m_color_map.insert(std::pair<String, CRGB>("DarkOrchid", CRGB::DarkOrchid));
    m_color_map.insert(std::pair<String, CRGB>("DarkRed", CRGB::DarkRed));
    m_color_map.insert(std::pair<String, CRGB>("DarkSalmon", CRGB::DarkSalmon));
    m_color_map.insert(std::pair<String, CRGB>("DarkSeaGreen", CRGB::DarkSeaGreen));
    m_color_map.insert(std::pair<String, CRGB>("DarkSlateBlue", CRGB::DarkSlateBlue));
    m_color_map.insert(std::pair<String, CRGB>("DarkSlateGray", CRGB::DarkSlateGray));
    m_color_map.insert(std::pair<String, CRGB>("DarkSlateGrey", CRGB::DarkSlateGrey));
    m_color_map.insert(std::pair<String, CRGB>("DarkTurquoise", CRGB::DarkTurquoise));
    m_color_map.insert(std::pair<String, CRGB>("DarkViolet", CRGB::DarkViolet));
    m_color_map.insert(std::pair<String, CRGB>("DeepPink", CRGB::DeepPink));
    m_color_map.insert(std::pair<String, CRGB>("DeepSkyBlue", CRGB::DeepSkyBlue));
    m_color_map.insert(std::pair<String, CRGB>("DimGray", CRGB::DimGray));
    m_color_map.insert(std::pair<String, CRGB>("DimGrey", CRGB::DimGrey));
    m_color_map.insert(std::pair<String, CRGB>("DodgerBlue", CRGB::DodgerBlue));
    m_color_map.insert(std::pair<String, CRGB>("FireBrick", CRGB::FireBrick));
    m_color_map.insert(std::pair<String, CRGB>("FloralWhite", CRGB::FloralWhite));
    m_color_map.insert(std::pair<String, CRGB>("ForestGreen", CRGB::ForestGreen));
    m_color_map.insert(std::pair<String, CRGB>("Fuchsia", CRGB::Fuchsia));
    m_color_map.insert(std::pair<String, CRGB>("Gainsboro", CRGB::Gainsboro));
    m_color_map.insert(std::pair<String, CRGB>("GhostWhite", CRGB::GhostWhite));
    m_color_map.insert(std::pair<String, CRGB>("Gold", CRGB::Gold));
    m_color_map.insert(std::pair<String, CRGB>("Goldenrod", CRGB::Goldenrod));
    m_color_map.insert(std::pair<String, CRGB>("Gray", CRGB::Gray));
    m_color_map.insert(std::pair<String, CRGB>("Grey", CRGB::Grey));
    m_color_map.insert(std::pair<String, CRGB>("Green", CRGB::Green));
    m_color_map.insert(std::pair<String, CRGB>("GreenYellow", CRGB::GreenYellow));
    m_color_map.insert(std::pair<String, CRGB>("Honeydew", CRGB::Honeydew));
    m_color_map.insert(std::pair<String, CRGB>("HotPink", CRGB::HotPink));
    m_color_map.insert(std::pair<String, CRGB>("IndianRed", CRGB::IndianRed));
    m_color_map.insert(std::pair<String, CRGB>("Indigo", CRGB::Indigo));
    m_color_map.insert(std::pair<String, CRGB>("Ivory", CRGB::Ivory));
    m_color_map.insert(std::pair<String, CRGB>("Khaki", CRGB::Khaki));
    m_color_map.insert(std::pair<String, CRGB>("Lavender", CRGB::Lavender));
    m_color_map.insert(std::pair<String, CRGB>("LavenderBlush", CRGB::LavenderBlush));
    m_color_map.insert(std::pair<String, CRGB>("LawnGreen", CRGB::LawnGreen));
    m_color_map.insert(std::pair<String, CRGB>("LemonChiffon", CRGB::LemonChiffon));
    m_color_map.insert(std::pair<String, CRGB>("LightBlue", CRGB::LightBlue));
    m_color_map.insert(std::pair<String, CRGB>("LightCoral", CRGB::LightCoral));
    m_color_map.insert(std::pair<String, CRGB>("LightCyan", CRGB::LightCyan));
    m_color_map.insert(std::pair<String, CRGB>("LightGoldenrodYellow", CRGB::LightGoldenrodYellow));
    m_color_map.insert(std::pair<String, CRGB>("LightGreen", CRGB::LightGreen));
    m_color_map.insert(std::pair<String, CRGB>("LightGrey", CRGB::LightGrey));
    m_color_map.insert(std::pair<String, CRGB>("LightPink", CRGB::LightPink));
    m_color_map.insert(std::pair<String, CRGB>("LightSalmon", CRGB::LightSalmon));
    m_color_map.insert(std::pair<String, CRGB>("LightSeaGreen", CRGB::LightSeaGreen));
    m_color_map.insert(std::pair<String, CRGB>("LightSkyBlue", CRGB::LightSkyBlue));
    m_color_map.insert(std::pair<String, CRGB>("LightSlateGray", CRGB::LightSlateGray));
    m_color_map.insert(std::pair<String, CRGB>("LightSlateGrey", CRGB::LightSlateGrey));
    m_color_map.insert(std::pair<String, CRGB>("LightSteelBlue", CRGB::LightSteelBlue));
    m_color_map.insert(std::pair<String, CRGB>("LightYellow", CRGB::LightYellow));
    m_color_map.insert(std::pair<String, CRGB>("Lime", CRGB::Lime));
    m_color_map.insert(std::pair<String, CRGB>("LimeGreen", CRGB::LimeGreen));
    m_color_map.insert(std::pair<String, CRGB>("Linen", CRGB::Linen));
    m_color_map.insert(std::pair<String, CRGB>("Magenta", CRGB::Magenta));
    m_color_map.insert(std::pair<String, CRGB>("Maroon", CRGB::Maroon));
    m_color_map.insert(std::pair<String, CRGB>("MediumAquamarine", CRGB::MediumAquamarine));
    m_color_map.insert(std::pair<String, CRGB>("MediumBlue", CRGB::MediumBlue));
    m_color_map.insert(std::pair<String, CRGB>("MediumOrchid", CRGB::MediumOrchid));
    m_color_map.insert(std::pair<String, CRGB>("MediumPurple", CRGB::MediumPurple));
    m_color_map.insert(std::pair<String, CRGB>("MediumSeaGreen", CRGB::MediumSeaGreen));
    m_color_map.insert(std::pair<String, CRGB>("MediumSlateBlue", CRGB::MediumSlateBlue));
    m_color_map.insert(std::pair<String, CRGB>("MediumSpringGreen", CRGB::MediumSpringGreen));
    m_color_map.insert(std::pair<String, CRGB>("MediumTurquoise", CRGB::MediumTurquoise));
    m_color_map.insert(std::pair<String, CRGB>("MediumVioletRed", CRGB::MediumVioletRed));
    m_color_map.insert(std::pair<String, CRGB>("MidnightBlue", CRGB::MidnightBlue));
    m_color_map.insert(std::pair<String, CRGB>("MintCream", CRGB::MintCream));
    m_color_map.insert(std::pair<String, CRGB>("MistyRose", CRGB::MistyRose));
    m_color_map.insert(std::pair<String, CRGB>("Moccasin", CRGB::Moccasin));
    m_color_map.insert(std::pair<String, CRGB>("NavajoWhite", CRGB::NavajoWhite));
    m_color_map.insert(std::pair<String, CRGB>("Navy", CRGB::Navy));
    m_color_map.insert(std::pair<String, CRGB>("OldLace", CRGB::OldLace));
    m_color_map.insert(std::pair<String, CRGB>("Olive", CRGB::Olive));
    m_color_map.insert(std::pair<String, CRGB>("OliveDrab", CRGB::OliveDrab));
    m_color_map.insert(std::pair<String, CRGB>("Orange", CRGB::Orange));
    m_color_map.insert(std::pair<String, CRGB>("OrangeRed", CRGB::OrangeRed));
    m_color_map.insert(std::pair<String, CRGB>("Orchid", CRGB::Orchid));
    m_color_map.insert(std::pair<String, CRGB>("PaleGoldenrod", CRGB::PaleGoldenrod));
    m_color_map.insert(std::pair<String, CRGB>("PaleGreen", CRGB::PaleGreen));
    m_color_map.insert(std::pair<String, CRGB>("PaleTurquoise", CRGB::PaleTurquoise));
    m_color_map.insert(std::pair<String, CRGB>("PaleVioletRed", CRGB::PaleVioletRed));
    m_color_map.insert(std::pair<String, CRGB>("PapayaWhip", CRGB::PapayaWhip));
    m_color_map.insert(std::pair<String, CRGB>("PeachPuff", CRGB::PeachPuff));
    m_color_map.insert(std::pair<String, CRGB>("Peru", CRGB::Peru));
    m_color_map.insert(std::pair<String, CRGB>("Pink", CRGB::Pink));
    m_color_map.insert(std::pair<String, CRGB>("Plaid", CRGB::Plaid));
    m_color_map.insert(std::pair<String, CRGB>("Plum", CRGB::Plum));
    m_color_map.insert(std::pair<String, CRGB>("PowderBlue", CRGB::PowderBlue));
    m_color_map.insert(std::pair<String, CRGB>("Purple", CRGB::Purple));
    m_color_map.insert(std::pair<String, CRGB>("Red", CRGB::Red));
    m_color_map.insert(std::pair<String, CRGB>("RosyBrown", CRGB::RosyBrown));
    m_color_map.insert(std::pair<String, CRGB>("RoyalBlue", CRGB::RoyalBlue));
    m_color_map.insert(std::pair<String, CRGB>("SaddleBrown", CRGB::SaddleBrown));
    m_color_map.insert(std::pair<String, CRGB>("Salmon", CRGB::Salmon));
    m_color_map.insert(std::pair<String, CRGB>("SandyBrown", CRGB::SandyBrown));
    m_color_map.insert(std::pair<String, CRGB>("SeaGreen", CRGB::SeaGreen));
    m_color_map.insert(std::pair<String, CRGB>("Seashell", CRGB::Seashell));
    m_color_map.insert(std::pair<String, CRGB>("Sienna", CRGB::Sienna));
    m_color_map.insert(std::pair<String, CRGB>("Silver", CRGB::Silver));
    m_color_map.insert(std::pair<String, CRGB>("SkyBlue", CRGB::SkyBlue));
    m_color_map.insert(std::pair<String, CRGB>("SlateBlue", CRGB::SlateBlue));
    m_color_map.insert(std::pair<String, CRGB>("SlateGray", CRGB::SlateGray));
    m_color_map.insert(std::pair<String, CRGB>("SlateGrey", CRGB::SlateGrey));
    m_color_map.insert(std::pair<String, CRGB>("Snow", CRGB::Snow));
    m_color_map.insert(std::pair<String, CRGB>("SpringGreen", CRGB::SpringGreen));
    m_color_map.insert(std::pair<String, CRGB>("SteelBlue", CRGB::SteelBlue));
    m_color_map.insert(std::pair<String, CRGB>("Tan", CRGB::Tan));
    m_color_map.insert(std::pair<String, CRGB>("Teal", CRGB::Teal));
    m_color_map.insert(std::pair<String, CRGB>("Thistle", CRGB::Thistle));
    m_color_map.insert(std::pair<String, CRGB>("Tomato", CRGB::Tomato));
    m_color_map.insert(std::pair<String, CRGB>("Turquoise", CRGB::Turquoise));
    m_color_map.insert(std::pair<String, CRGB>("Violet", CRGB::Violet));
    m_color_map.insert(std::pair<String, CRGB>("Wheat", CRGB::Wheat));
    m_color_map.insert(std::pair<String, CRGB>("White", CRGB::White));
    m_color_map.insert(std::pair<String, CRGB>("WhiteSmoke", CRGB::WhiteSmoke));
    m_color_map.insert(std::pair<String, CRGB>("Yellow", CRGB::Yellow));
    m_color_map.insert(std::pair<String, CRGB>("YellowGreen", CRGB::YellowGreen));
}

void Led::setup()
{
    m_next_blink_time = millis();
    FastLED.addLeds<WS2812, LED_PIN, GRB>(m_strip, LED_NUM);
    FastLED.setBrightness(255);
    fill_color_map();
}

void Led::loop()
{
    if (!m_enabled)
        return;

    if (m_error_code != 0)
        led_error();
    else
        starry_night();
}

void Led::setBrightness(int b)
{
    FastLED.setBrightness(b);
    m_brightness = b;
    FastLED.show();
}

void Led::setErrorCode(int code)
{
    m_error_code = code;
}

void Led::setEnabled(bool e)
{
    m_enabled = e;
    FastLED.setBrightness(e ? m_brightness : 0);
    FastLED.show();
}

void Led::setColor(String color_in)
{
    m_color_str = color_in;
    m_color = m_color_map[m_color_str];
}

String Led::getColor()
{
    return m_color_str;
}

String Led::getHtmlColors()
{
    String str;

    std::map<String, CRGB>::iterator it = m_color_map.begin();
    while (it != m_color_map.end()) {
        String color = it->first;
        str += "    <option value=\"";
        str += color;
        str += "\"";
        if (color == m_color_str)
            str += " selected";
        str += ">";
        str += color;
        str += "</option>\n";
        it++;
    }

    return str;
}
