// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/

// #define FASTLED_ALL_PINS_HARDWARE_SPI
// #define FASTLED_ESP8266_RAW_PIN_ORDER
// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
// #define FASTLED_ESP8266_D1_PIN_ORDER

#include <FastLED.h>
#include <map>

static void starry_night()
{
    for (int i = 0; i < LED_NUM; ++i)
        strip[i] = color;

    static long int unset_time = 0;

    if (unset_time) {
        unset_time = 0;
        FastLED.show();
        return;
    }

    if (millis() < next_blink_time)
        return;

    unset_time = millis() + 50;

    for (int i = 0; i < LED_NUM / 10; ++i)
        strip[rand() % LED_NUM] = CRGB::White;

    next_blink_time += rand() % 10000;

    int step = 100;
    int b = FastLED.getBrightness() - step + rand() % step;
    FastLED.setBrightness(b);
    FastLED.show();

    return;
}

static void led_error()
{
    if (millis() < next_blink_time)
        return;

    FastLED.setBrightness((FastLED.getBrightness() == brightness) ? 0 : brightness);
    FastLED.show();

    next_blink_time += 500;
}

static void fill_color_map()
{
    color_map.insert(std::pair<String, CRGB>("Amethyst", CRGB::Amethyst));
    color_map.insert(std::pair<String, CRGB>("AntiqueWhite", CRGB::AntiqueWhite));
    color_map.insert(std::pair<String, CRGB>("Aqua", CRGB::Aqua));
    color_map.insert(std::pair<String, CRGB>("Aquamarine", CRGB::Aquamarine));
    color_map.insert(std::pair<String, CRGB>("Azure", CRGB::Azure));
    color_map.insert(std::pair<String, CRGB>("Beige", CRGB::Beige));
    color_map.insert(std::pair<String, CRGB>("Bisque", CRGB::Bisque));
    color_map.insert(std::pair<String, CRGB>("Black", CRGB::Black));
    color_map.insert(std::pair<String, CRGB>("BlanchedAlmond", CRGB::BlanchedAlmond));
    color_map.insert(std::pair<String, CRGB>("Blue", CRGB::Blue));
    color_map.insert(std::pair<String, CRGB>("BlueViolet", CRGB::BlueViolet));
    color_map.insert(std::pair<String, CRGB>("Brown", CRGB::Brown));
    color_map.insert(std::pair<String, CRGB>("BurlyWood", CRGB::BurlyWood));
    color_map.insert(std::pair<String, CRGB>("CadetBlue", CRGB::CadetBlue));
    color_map.insert(std::pair<String, CRGB>("Chartreuse", CRGB::Chartreuse));
    color_map.insert(std::pair<String, CRGB>("Chocolate", CRGB::Chocolate));
    color_map.insert(std::pair<String, CRGB>("Coral", CRGB::Coral));
    color_map.insert(std::pair<String, CRGB>("CornflowerBlue", CRGB::CornflowerBlue));
    color_map.insert(std::pair<String, CRGB>("Cornsilk", CRGB::Cornsilk));
    color_map.insert(std::pair<String, CRGB>("Crimson", CRGB::Crimson));
    color_map.insert(std::pair<String, CRGB>("Cyan", CRGB::Cyan));
    color_map.insert(std::pair<String, CRGB>("DarkBlue", CRGB::DarkBlue));
    color_map.insert(std::pair<String, CRGB>("DarkCyan", CRGB::DarkCyan));
    color_map.insert(std::pair<String, CRGB>("DarkGoldenrod", CRGB::DarkGoldenrod));
    color_map.insert(std::pair<String, CRGB>("DarkGray", CRGB::DarkGray));
    color_map.insert(std::pair<String, CRGB>("DarkGrey", CRGB::DarkGrey));
    color_map.insert(std::pair<String, CRGB>("DarkGreen", CRGB::DarkGreen));
    color_map.insert(std::pair<String, CRGB>("DarkKhaki", CRGB::DarkKhaki));
    color_map.insert(std::pair<String, CRGB>("DarkMagenta", CRGB::DarkMagenta));
    color_map.insert(std::pair<String, CRGB>("DarkOliveGreen", CRGB::DarkOliveGreen));
    color_map.insert(std::pair<String, CRGB>("DarkOrange", CRGB::DarkOrange));
    color_map.insert(std::pair<String, CRGB>("DarkOrchid", CRGB::DarkOrchid));
    color_map.insert(std::pair<String, CRGB>("DarkRed", CRGB::DarkRed));
    color_map.insert(std::pair<String, CRGB>("DarkSalmon", CRGB::DarkSalmon));
    color_map.insert(std::pair<String, CRGB>("DarkSeaGreen", CRGB::DarkSeaGreen));
    color_map.insert(std::pair<String, CRGB>("DarkSlateBlue", CRGB::DarkSlateBlue));
    color_map.insert(std::pair<String, CRGB>("DarkSlateGray", CRGB::DarkSlateGray));
    color_map.insert(std::pair<String, CRGB>("DarkSlateGrey", CRGB::DarkSlateGrey));
    color_map.insert(std::pair<String, CRGB>("DarkTurquoise", CRGB::DarkTurquoise));
    color_map.insert(std::pair<String, CRGB>("DarkViolet", CRGB::DarkViolet));
    color_map.insert(std::pair<String, CRGB>("DeepPink", CRGB::DeepPink));
    color_map.insert(std::pair<String, CRGB>("DeepSkyBlue", CRGB::DeepSkyBlue));
    color_map.insert(std::pair<String, CRGB>("DimGray", CRGB::DimGray));
    color_map.insert(std::pair<String, CRGB>("DimGrey", CRGB::DimGrey));
    color_map.insert(std::pair<String, CRGB>("DodgerBlue", CRGB::DodgerBlue));
    color_map.insert(std::pair<String, CRGB>("FireBrick", CRGB::FireBrick));
    color_map.insert(std::pair<String, CRGB>("FloralWhite", CRGB::FloralWhite));
    color_map.insert(std::pair<String, CRGB>("ForestGreen", CRGB::ForestGreen));
    color_map.insert(std::pair<String, CRGB>("Fuchsia", CRGB::Fuchsia));
    color_map.insert(std::pair<String, CRGB>("Gainsboro", CRGB::Gainsboro));
    color_map.insert(std::pair<String, CRGB>("GhostWhite", CRGB::GhostWhite));
    color_map.insert(std::pair<String, CRGB>("Gold", CRGB::Gold));
    color_map.insert(std::pair<String, CRGB>("Goldenrod", CRGB::Goldenrod));
    color_map.insert(std::pair<String, CRGB>("Gray", CRGB::Gray));
    color_map.insert(std::pair<String, CRGB>("Grey", CRGB::Grey));
    color_map.insert(std::pair<String, CRGB>("Green", CRGB::Green));
    color_map.insert(std::pair<String, CRGB>("GreenYellow", CRGB::GreenYellow));
    color_map.insert(std::pair<String, CRGB>("Honeydew", CRGB::Honeydew));
    color_map.insert(std::pair<String, CRGB>("HotPink", CRGB::HotPink));
    color_map.insert(std::pair<String, CRGB>("IndianRed", CRGB::IndianRed));
    color_map.insert(std::pair<String, CRGB>("Indigo", CRGB::Indigo));
    color_map.insert(std::pair<String, CRGB>("Ivory", CRGB::Ivory));
    color_map.insert(std::pair<String, CRGB>("Khaki", CRGB::Khaki));
    color_map.insert(std::pair<String, CRGB>("Lavender", CRGB::Lavender));
    color_map.insert(std::pair<String, CRGB>("LavenderBlush", CRGB::LavenderBlush));
    color_map.insert(std::pair<String, CRGB>("LawnGreen", CRGB::LawnGreen));
    color_map.insert(std::pair<String, CRGB>("LemonChiffon", CRGB::LemonChiffon));
    color_map.insert(std::pair<String, CRGB>("LightBlue", CRGB::LightBlue));
    color_map.insert(std::pair<String, CRGB>("LightCoral", CRGB::LightCoral));
    color_map.insert(std::pair<String, CRGB>("LightCyan", CRGB::LightCyan));
    color_map.insert(std::pair<String, CRGB>("LightGoldenrodYellow", CRGB::LightGoldenrodYellow));
    color_map.insert(std::pair<String, CRGB>("LightGreen", CRGB::LightGreen));
    color_map.insert(std::pair<String, CRGB>("LightGrey", CRGB::LightGrey));
    color_map.insert(std::pair<String, CRGB>("LightPink", CRGB::LightPink));
    color_map.insert(std::pair<String, CRGB>("LightSalmon", CRGB::LightSalmon));
    color_map.insert(std::pair<String, CRGB>("LightSeaGreen", CRGB::LightSeaGreen));
    color_map.insert(std::pair<String, CRGB>("LightSkyBlue", CRGB::LightSkyBlue));
    color_map.insert(std::pair<String, CRGB>("LightSlateGray", CRGB::LightSlateGray));
    color_map.insert(std::pair<String, CRGB>("LightSlateGrey", CRGB::LightSlateGrey));
    color_map.insert(std::pair<String, CRGB>("LightSteelBlue", CRGB::LightSteelBlue));
    color_map.insert(std::pair<String, CRGB>("LightYellow", CRGB::LightYellow));
    color_map.insert(std::pair<String, CRGB>("Lime", CRGB::Lime));
    color_map.insert(std::pair<String, CRGB>("LimeGreen", CRGB::LimeGreen));
    color_map.insert(std::pair<String, CRGB>("Linen", CRGB::Linen));
    color_map.insert(std::pair<String, CRGB>("Magenta", CRGB::Magenta));
    color_map.insert(std::pair<String, CRGB>("Maroon", CRGB::Maroon));
    color_map.insert(std::pair<String, CRGB>("MediumAquamarine", CRGB::MediumAquamarine));
    color_map.insert(std::pair<String, CRGB>("MediumBlue", CRGB::MediumBlue));
    color_map.insert(std::pair<String, CRGB>("MediumOrchid", CRGB::MediumOrchid));
    color_map.insert(std::pair<String, CRGB>("MediumPurple", CRGB::MediumPurple));
    color_map.insert(std::pair<String, CRGB>("MediumSeaGreen", CRGB::MediumSeaGreen));
    color_map.insert(std::pair<String, CRGB>("MediumSlateBlue", CRGB::MediumSlateBlue));
    color_map.insert(std::pair<String, CRGB>("MediumSpringGreen", CRGB::MediumSpringGreen));
    color_map.insert(std::pair<String, CRGB>("MediumTurquoise", CRGB::MediumTurquoise));
    color_map.insert(std::pair<String, CRGB>("MediumVioletRed", CRGB::MediumVioletRed));
    color_map.insert(std::pair<String, CRGB>("MidnightBlue", CRGB::MidnightBlue));
    color_map.insert(std::pair<String, CRGB>("MintCream", CRGB::MintCream));
    color_map.insert(std::pair<String, CRGB>("MistyRose", CRGB::MistyRose));
    color_map.insert(std::pair<String, CRGB>("Moccasin", CRGB::Moccasin));
    color_map.insert(std::pair<String, CRGB>("NavajoWhite", CRGB::NavajoWhite));
    color_map.insert(std::pair<String, CRGB>("Navy", CRGB::Navy));
    color_map.insert(std::pair<String, CRGB>("OldLace", CRGB::OldLace));
    color_map.insert(std::pair<String, CRGB>("Olive", CRGB::Olive));
    color_map.insert(std::pair<String, CRGB>("OliveDrab", CRGB::OliveDrab));
    color_map.insert(std::pair<String, CRGB>("Orange", CRGB::Orange));
    color_map.insert(std::pair<String, CRGB>("OrangeRed", CRGB::OrangeRed));
    color_map.insert(std::pair<String, CRGB>("Orchid", CRGB::Orchid));
    color_map.insert(std::pair<String, CRGB>("PaleGoldenrod", CRGB::PaleGoldenrod));
    color_map.insert(std::pair<String, CRGB>("PaleGreen", CRGB::PaleGreen));
    color_map.insert(std::pair<String, CRGB>("PaleTurquoise", CRGB::PaleTurquoise));
    color_map.insert(std::pair<String, CRGB>("PaleVioletRed", CRGB::PaleVioletRed));
    color_map.insert(std::pair<String, CRGB>("PapayaWhip", CRGB::PapayaWhip));
    color_map.insert(std::pair<String, CRGB>("PeachPuff", CRGB::PeachPuff));
    color_map.insert(std::pair<String, CRGB>("Peru", CRGB::Peru));
    color_map.insert(std::pair<String, CRGB>("Pink", CRGB::Pink));
    color_map.insert(std::pair<String, CRGB>("Plaid", CRGB::Plaid));
    color_map.insert(std::pair<String, CRGB>("Plum", CRGB::Plum));
    color_map.insert(std::pair<String, CRGB>("PowderBlue", CRGB::PowderBlue));
    color_map.insert(std::pair<String, CRGB>("Purple", CRGB::Purple));
    color_map.insert(std::pair<String, CRGB>("Red", CRGB::Red));
    color_map.insert(std::pair<String, CRGB>("RosyBrown", CRGB::RosyBrown));
    color_map.insert(std::pair<String, CRGB>("RoyalBlue", CRGB::RoyalBlue));
    color_map.insert(std::pair<String, CRGB>("SaddleBrown", CRGB::SaddleBrown));
    color_map.insert(std::pair<String, CRGB>("Salmon", CRGB::Salmon));
    color_map.insert(std::pair<String, CRGB>("SandyBrown", CRGB::SandyBrown));
    color_map.insert(std::pair<String, CRGB>("SeaGreen", CRGB::SeaGreen));
    color_map.insert(std::pair<String, CRGB>("Seashell", CRGB::Seashell));
    color_map.insert(std::pair<String, CRGB>("Sienna", CRGB::Sienna));
    color_map.insert(std::pair<String, CRGB>("Silver", CRGB::Silver));
    color_map.insert(std::pair<String, CRGB>("SkyBlue", CRGB::SkyBlue));
    color_map.insert(std::pair<String, CRGB>("SlateBlue", CRGB::SlateBlue));
    color_map.insert(std::pair<String, CRGB>("SlateGray", CRGB::SlateGray));
    color_map.insert(std::pair<String, CRGB>("SlateGrey", CRGB::SlateGrey));
    color_map.insert(std::pair<String, CRGB>("Snow", CRGB::Snow));
    color_map.insert(std::pair<String, CRGB>("SpringGreen", CRGB::SpringGreen));
    color_map.insert(std::pair<String, CRGB>("SteelBlue", CRGB::SteelBlue));
    color_map.insert(std::pair<String, CRGB>("Tan", CRGB::Tan));
    color_map.insert(std::pair<String, CRGB>("Teal", CRGB::Teal));
    color_map.insert(std::pair<String, CRGB>("Thistle", CRGB::Thistle));
    color_map.insert(std::pair<String, CRGB>("Tomato", CRGB::Tomato));
    color_map.insert(std::pair<String, CRGB>("Turquoise", CRGB::Turquoise));
    color_map.insert(std::pair<String, CRGB>("Violet", CRGB::Violet));
    color_map.insert(std::pair<String, CRGB>("Wheat", CRGB::Wheat));
    color_map.insert(std::pair<String, CRGB>("White", CRGB::White));
    color_map.insert(std::pair<String, CRGB>("WhiteSmoke", CRGB::WhiteSmoke));
    color_map.insert(std::pair<String, CRGB>("Yellow", CRGB::Yellow));
    color_map.insert(std::pair<String, CRGB>("YellowGreen", CRGB::YellowGreen));
}

void led_setup()
{
    color = CRGB::Red;
    next_blink_time = millis();
    FastLED.addLeds<WS2812, LED_PIN, GRB>(strip, LED_NUM);
    FastLED.setBrightness(255);
    fill_color_map();
}

void led_loop()
{
    if (!enabled)
        return;

    if (error_code != 0)
        led_error();
    else
        starry_night();
}

void led_set_brightness(int b)
{
    Serial.println(b);
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

void led_set_color(String color_in)
{
    Serial.println(color_in);
    color_str = color_in;
    color = color_map[color_str];
}

String led_get_color()
{
    return color_str;
}

String led_get_html_colors()
{
    String str;

    std::map<String, CRGB>::iterator it = color_map.begin();
    while (it != color_map.end()) {
        String color = it->first;
        str += "    <option value=\"";
        str += color;
        str += "\"";
        if (color == color_str)
            str += " selected";
        str += ">";
        str += color;
        str += "</option>\n";
        it++;
    }

    return str;
}
