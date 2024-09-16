// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#FastLEDFramework

// #define FASTLED_ALL_PINS_HARDWARE_SPI
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER

#include "config.h"
#include "led.h"

static Led led;
Led &Led::Instance()
{
    return led;
}

void Led::fillColorMap()
{
    auto I = [&](const String &N, const CRGB &V) { m_color_map.insert(std::pair<String, CRGB>(N, V)); };

    I("Amethyst", CRGB::Amethyst);
    I("AntiqueWhite", CRGB::AntiqueWhite);
    I("Aqua", CRGB::Aqua);
    I("Aquamarine", CRGB::Aquamarine);
    I("Azure", CRGB::Azure);
    I("Beige", CRGB::Beige);
    I("Bisque", CRGB::Bisque);
    I("Black", CRGB::Black);
    I("BlanchedAlmond", CRGB::BlanchedAlmond);
    I("Blue", CRGB::Blue);
    I("BlueViolet", CRGB::BlueViolet);
    I("Brown", CRGB::Brown);
    I("BurlyWood", CRGB::BurlyWood);
    I("CadetBlue", CRGB::CadetBlue);
    I("Chartreuse", CRGB::Chartreuse);
    I("Chocolate", CRGB::Chocolate);
    I("Coral", CRGB::Coral);
    I("CornflowerBlue", CRGB::CornflowerBlue);
    I("Cornsilk", CRGB::Cornsilk);
    I("Crimson", CRGB::Crimson);
    I("Cyan", CRGB::Cyan);
    I("DarkBlue", CRGB::DarkBlue);
    I("DarkCyan", CRGB::DarkCyan);
    I("DarkGoldenrod", CRGB::DarkGoldenrod);
    I("DarkGray", CRGB::DarkGray);
    I("DarkGrey", CRGB::DarkGrey);
    I("DarkGreen", CRGB::DarkGreen);
    I("DarkKhaki", CRGB::DarkKhaki);
    I("DarkMagenta", CRGB::DarkMagenta);
    I("DarkOliveGreen", CRGB::DarkOliveGreen);
    I("DarkOrange", CRGB::DarkOrange);
    I("DarkOrchid", CRGB::DarkOrchid);
    I("DarkRed", CRGB::DarkRed);
    I("DarkSalmon", CRGB::DarkSalmon);
    I("DarkSeaGreen", CRGB::DarkSeaGreen);
    I("DarkSlateBlue", CRGB::DarkSlateBlue);
    I("DarkSlateGray", CRGB::DarkSlateGray);
    I("DarkSlateGrey", CRGB::DarkSlateGrey);
    I("DarkTurquoise", CRGB::DarkTurquoise);
    I("DarkViolet", CRGB::DarkViolet);
    I("DeepPink", CRGB::DeepPink);
    I("DeepSkyBlue", CRGB::DeepSkyBlue);
    I("DimGray", CRGB::DimGray);
    I("DimGrey", CRGB::DimGrey);
    I("DodgerBlue", CRGB::DodgerBlue);
    I("FireBrick", CRGB::FireBrick);
    I("FloralWhite", CRGB::FloralWhite);
    I("ForestGreen", CRGB::ForestGreen);
    I("Fuchsia", CRGB::Fuchsia);
    I("Gainsboro", CRGB::Gainsboro);
    I("GhostWhite", CRGB::GhostWhite);
    I("Gold", CRGB::Gold);
    I("Goldenrod", CRGB::Goldenrod);
    I("Gray", CRGB::Gray);
    I("Grey", CRGB::Grey);
    I("Green", CRGB::Green);
    I("GreenYellow", CRGB::GreenYellow);
    I("Honeydew", CRGB::Honeydew);
    I("HotPink", CRGB::HotPink);
    I("IndianRed", CRGB::IndianRed);
    I("Indigo", CRGB::Indigo);
    I("Ivory", CRGB::Ivory);
    I("Khaki", CRGB::Khaki);
    I("Lavender", CRGB::Lavender);
    I("LavenderBlush", CRGB::LavenderBlush);
    I("LawnGreen", CRGB::LawnGreen);
    I("LemonChiffon", CRGB::LemonChiffon);
    I("LightBlue", CRGB::LightBlue);
    I("LightCoral", CRGB::LightCoral);
    I("LightCyan", CRGB::LightCyan);
    I("LightGoldenrodYellow", CRGB::LightGoldenrodYellow);
    I("LightGreen", CRGB::LightGreen);
    I("LightGrey", CRGB::LightGrey);
    I("LightPink", CRGB::LightPink);
    I("LightSalmon", CRGB::LightSalmon);
    I("LightSeaGreen", CRGB::LightSeaGreen);
    I("LightSkyBlue", CRGB::LightSkyBlue);
    I("LightSlateGray", CRGB::LightSlateGray);
    I("LightSlateGrey", CRGB::LightSlateGrey);
    I("LightSteelBlue", CRGB::LightSteelBlue);
    I("LightYellow", CRGB::LightYellow);
    I("Lime", CRGB::Lime);
    I("LimeGreen", CRGB::LimeGreen);
    I("Linen", CRGB::Linen);
    I("Magenta", CRGB::Magenta);
    I("Maroon", CRGB::Maroon);
    I("MediumAquamarine", CRGB::MediumAquamarine);
    I("MediumBlue", CRGB::MediumBlue);
    I("MediumOrchid", CRGB::MediumOrchid);
    I("MediumPurple", CRGB::MediumPurple);
    I("MediumSeaGreen", CRGB::MediumSeaGreen);
    I("MediumSlateBlue", CRGB::MediumSlateBlue);
    I("MediumSpringGreen", CRGB::MediumSpringGreen);
    I("MediumTurquoise", CRGB::MediumTurquoise);
    I("MediumVioletRed", CRGB::MediumVioletRed);
    I("MidnightBlue", CRGB::MidnightBlue);
    I("MintCream", CRGB::MintCream);
    I("MistyRose", CRGB::MistyRose);
    I("Moccasin", CRGB::Moccasin);
    I("NavajoWhite", CRGB::NavajoWhite);
    I("Navy", CRGB::Navy);
    I("OldLace", CRGB::OldLace);
    I("Olive", CRGB::Olive);
    I("OliveDrab", CRGB::OliveDrab);
    I("Orange", CRGB::Orange);
    I("OrangeRed", CRGB::OrangeRed);
    I("Orchid", CRGB::Orchid);
    I("PaleGoldenrod", CRGB::PaleGoldenrod);
    I("PaleGreen", CRGB::PaleGreen);
    I("PaleTurquoise", CRGB::PaleTurquoise);
    I("PaleVioletRed", CRGB::PaleVioletRed);
    I("PapayaWhip", CRGB::PapayaWhip);
    I("PeachPuff", CRGB::PeachPuff);
    I("Peru", CRGB::Peru);
    I("Pink", CRGB::Pink);
    I("Plaid", CRGB::Plaid);
    I("Plum", CRGB::Plum);
    I("PowderBlue", CRGB::PowderBlue);
    I("Purple", CRGB::Purple);
    I("Red", CRGB::Red);
    I("RosyBrown", CRGB::RosyBrown);
    I("RoyalBlue", CRGB::RoyalBlue);
    I("SaddleBrown", CRGB::SaddleBrown);
    I("Salmon", CRGB::Salmon);
    I("SandyBrown", CRGB::SandyBrown);
    I("SeaGreen", CRGB::SeaGreen);
    I("Seashell", CRGB::Seashell);
    I("Sienna", CRGB::Sienna);
    I("Silver", CRGB::Silver);
    I("SkyBlue", CRGB::SkyBlue);
    I("SlateBlue", CRGB::SlateBlue);
    I("SlateGray", CRGB::SlateGray);
    I("SlateGrey", CRGB::SlateGrey);
    I("Snow", CRGB::Snow);
    I("SpringGreen", CRGB::SpringGreen);
    I("SteelBlue", CRGB::SteelBlue);
    I("Tan", CRGB::Tan);
    I("Teal", CRGB::Teal);
    I("Thistle", CRGB::Thistle);
    I("Tomato", CRGB::Tomato);
    I("Turquoise", CRGB::Turquoise);
    I("Violet", CRGB::Violet);
    I("Wheat", CRGB::Wheat);
    I("White", CRGB::White);
    I("WhiteSmoke", CRGB::WhiteSmoke);
    I("Yellow", CRGB::Yellow);
    I("YellowGreen", CRGB::YellowGreen);
}

void Led::fillEffectsMap()
{
    auto I = [&](const String &N, const std::map<String, int> &V) {
        m_effect_map.insert(std::pair<String, std::map<String, int>>(N, V));
    };

    I("StarryNight", {{"Speed", 300}, {"UnsetTime", 50}});
    I("BouncingColoredBalls", {{"color1(hex)", 0x6f0035}, {"color2(hex)", 0x5e00ff}, {"color3(hex)", 0xC46B65}});
    I("BouncingBalls", {{"BallCount", 3}});
    I("ColorWipe", {{"SpeedDelay", 50}});
    I("CylonBounce", {{"EyeSize", 4}, {"ReturnDelay", 15}, {"SpeedDelay", 10}});
    I("Fire", {{"Cooling", 55}, {"Sparking", 120}, {"SpeedDelay", 15}});
    I("HalloweenEyes", {{"EyeSpace", 4}, {"EyeWidth", 1}, {"Fade", true}});
    I("RainbowCycle", {{"SpeedDelay", 20}});
    I("TwinkleRandom", {{"Count", 20}, {"OnlyOne", 0}, {"SpeedDelay", 100}});
    I("RunningLights", {{"WaveDelay", 50}});
    I("SnowSparkle", {{"SparkleDelay", 20}});
    I("Sparkle", {{"SpeedDelay", 0}});
    I("Strobe", {{"EndPause", 50}, {"FlashDelay", 1000}, {"StrobeCount", 3}});
    I("TheaterChaseRainbow", {{"SpeedDelay", 50}});
    I("TheaterChase", {{"SpeedDelay", 50}});
    I("Twinkle", {{"Count", 10}, {"OnlyOne", false}, {"SpeedDelay", 100}});
}

void Led::setup()
{
    FastLED.addLeds<WS2812, GPIO_LED_STRIP_PIN, GRB>(m_strip, LED_STRIP_LEDSNUM);
    fillColorMap();
    fillEffectsMap();

    setAll(0, 0, 0);

#ifdef DETECT_LEDS_COUNT
    for (int i = 0; i < LED_STRIP_LEDSNUM; i++) {
        setPixel(i, 255, 0, 0);
        ::delay(1000);
        Serial.print("Led::setup ");
        Serial.println(i);
        showStrip();
    }
#endif
}

void Led::loop()
{
    auto exec = [&](const String &effect) {
        if (effect == "StarryNight") {
            StarryNight();
        } else if (effect == "BouncingColoredBalls") {
            BouncingColoredBalls();
        } else if (effect == "BouncingBalls") {
            BouncingBalls();
        } else if (effect == "ColorWipe") {
            ColorWipe();
        } else if (effect == "CylonBounce") {
            CylonBounce();
        } else if (effect == "FadeInOut") {
            FadeInOut();
        } else if (effect == "Fire") {
            Fire();
        } else if (effect == "HalloweenEyes") {
            HalloweenEyes();
        } else if (effect == "RainbowCycle") {
            RainbowCycle();
        } else if (effect == "TwinkleRandom") {
            TwinkleRandom();
        } else if (effect == "RunningLights") {
            RunningLights();
        } else if (effect == "SnowSparkle") {
            SnowSparkle();
        } else if (effect == "Sparkle") {
            Sparkle();
        } else if (effect == "Strobe") {
            Strobe();
        } else if (effect == "TheaterChaseRainbow") {
            TheaterChaseRainbow();
        } else if (effect == "TheaterChase") {
            TheaterChase();
        } else if (effect == "Twinkle") {
            Twinkle();
        }
    };

    bool show = (m_enabled || m_force_on) && !m_force_off;
    int brightness = show ? m_brightness : 0;

    if (brightness != m_current_brightness) {
        FastLED.setBrightness(brightness);
        m_current_brightness = brightness;
        showStrip();
    }

    if (!show)
        return;

    if (m_error_code && !m_silence_error)
        exec(m_error_effect);
    else
        exec(m_effect);
}

void Led::setBrightness(int b)
{
    Serial.print("Led::setBrightness ");
    Serial.println(b);
    FastLED.setBrightness(b);
    m_brightness = b;
    m_current_brightness = b;
    showStrip();
}

void Led::setErrorCode(int code)
{
    if (m_error_code != code) {
        m_theme_state = 0;
        m_delay = 0;
        m_error_code = code;
    }
}

void Led::setColor(String color_in)
{
    Serial.print("Led::setColor ");
    Serial.println(color_in);
    m_color_str = color_in;
    m_color = m_color_map[m_color_str];
}

void Led::setEffect(String color_in)
{
    m_theme_state = 0;
    m_delay = 0;
    Serial.print("Led::setEffect ");
    Serial.println(color_in);
    m_effect = color_in;
}

void Led::setErrorEffect(String color_in)
{
    m_theme_state = 0;
    m_delay = 0;
    Serial.print("Led::setErrorEffect ");
    Serial.println(color_in);
    m_error_effect = color_in;
}

void Led::setEffectArg(int idx, int arg)
{
    Serial.print("Led::setEffectArg ");
    Serial.print(idx);
    Serial.print("=>");
    Serial.println(arg);

    auto effect = m_effect_map.find(m_effect);

    if (effect == m_effect_map.end())
        return;

    auto effect_data = effect->second;

    if (idx >= effect_data.size())
        return;

    std::map<String, int>::iterator it = effect_data.begin();

    for (int i = 0; i < idx; i++)
        it++;

    effect->second.erase(it->first);
    effect->second.insert(std::pair<String, int>(it->first, arg));
}

int Led::getEffectArg(int idx)
{
    auto effect = m_effect_map.find(m_effect);

    if (effect == m_effect_map.end())
        return 0;

    auto effect_data = effect->second;

    if (idx >= effect_data.size())
        return 0;

    std::map<String, int>::iterator it = effect_data.begin();

    for (int i = 0; i < idx; i++)
        it++;

    return it->second;
}

String Led::getColors()
{
    String str;

    std::map<String, CRGB>::iterator it = m_color_map.begin();
    while (it != m_color_map.end()) {
        if (it != m_color_map.begin())
            str += ", ";
        String color = it->first;
        str += "\"";
        str += color;
        str += "\"";
        it++;
    }

    return str;
}

String Led::getEffects()
{
    String str;

    std::map<String, std::map<String, int>>::iterator it = m_effect_map.begin();
    while (it != m_effect_map.end()) {
        if (it != m_effect_map.begin())
            str += ", ";
        String effect = it->first;
        str += "\"";
        str += effect;
        str += "\"";
        it++;
    }

    return str;
}

String Led::getArguments()
{
    String str;

    auto effect = m_effect_map.find(m_effect);

    if (effect == m_effect_map.end())
        return str;

    auto effect_data = effect->second;

    std::map<String, int>::iterator it = effect_data.begin();
    while (it != effect_data.end()) {
        if (it != effect_data.begin())
            str += ", ";
        String key = it->first;
        String value = String(it->second);
        str += R"( ")" + key + R"(": )" + value + R"()";
        it++;
    }
    return str;
}

void Led::showStrip()
{
    if (m_debug) {
        for (int i = 0; i < LED_STRIP_LEDSNUM; i++) {
            bool show = m_strip[i].r || m_strip[i].g || m_strip[i].b;
            String show_str = m_current_brightness ? "*" : "_";
            Serial.print(show ? show_str : " ");
        }
        Serial.print(" ");
        Serial.print(m_current_brightness);
        Serial.print(" ");
        Serial.println(m_color_str);
    }

    FastLED.show();
}

void Led::setPixel(int Pixel, byte red, byte green, byte blue)
{
    m_strip[Pixel].r = red;
    m_strip[Pixel].g = green;
    m_strip[Pixel].b = blue;
}

void Led::setAll(byte red, byte green, byte blue)
{
    for (int i = 0; i < LED_STRIP_LEDSNUM; i++) {
        setPixel(i, red, green, blue);
    }
    showStrip();
}

// clang-format off
#define DEF_COLOR \
    byte red = m_color.r; \
    byte green = m_color.g; \
    byte blue = m_color.b; \
    auto eff_data = m_effect_map.find(__func__); \
    if (eff_data == m_effect_map.end()) \
        return; \
    auto args = eff_data->second;
// clang-format on

void Led::StarryNight()
{
    DEF_COLOR

    int theme_state = m_theme_state;

    switch (m_theme_state) {
    case 0: {
        int UnsetTime = args["UnsetTime"];

        for (int i = 0; i < LED_STRIP_LEDSNUM / 10; ++i)
            m_strip[rand() % LED_STRIP_LEDSNUM] = CRGB::White;
        showStrip();
        delay(UnsetTime);
        m_theme_state = 1;
        break;
    }
    case 1: {
        if (!delay_is_finished())
            return;

        int Speed = args["Speed"];
        for (int i = 0; i < LED_STRIP_LEDSNUM; ++i)
            m_strip[i] = m_color;

        showStrip();

        delay(rand() % Speed);
        m_theme_state = 2;
        break;
    }
    case 2: {
        if (delay_is_finished())
            m_theme_state = 0;
        break;
    }
    }

    return;
}

void Led::BouncingColoredBalls()
{
    int BallCount = 3;
    byte colors[3][3];

    DEF_COLOR

    auto fill_colors = [&](int i) {
        String color_id = String("color") + String(i) + String("hex");
        colors[i][0] = ((args[color_id] >> 16) & 0xFF);
        colors[i][1] = ((args[color_id] >> 8) & 0xFF);
        colors[i][2] = ((args[color_id]) & 0xFF);
    };

    for (int i = 0; i < BallCount; ++i)
        fill_colors(i);

    float Gravity = -9.81;
    int StartHeight = 1;

    static float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);

    static float *Height;
    static float *ImpactVelocity;
    static float *TimeSinceLastBounce;
    static int *Position;
    static long *ClockTimeSinceLastBounce;
    static float *Dampening;

    static int m_BallCount = 0;

    if (m_BallCount != BallCount) {
        if (m_BallCount) {
            free(Height);
            free(ImpactVelocity);
            free(TimeSinceLastBounce);
            free(Position);
            free(ClockTimeSinceLastBounce);
            free(Dampening);
        }

        Height = (float *)malloc(sizeof(float) * BallCount);
        ImpactVelocity = (float *)malloc(sizeof(float) * BallCount);
        TimeSinceLastBounce = (float *)malloc(sizeof(float) * BallCount);
        Position = (int *)malloc(sizeof(float) * BallCount);
        ClockTimeSinceLastBounce = (long *)malloc(sizeof(float) * BallCount);
        Dampening = (float *)malloc(sizeof(float) * BallCount);

        for (int i = 0; i < BallCount; i++) {
            ClockTimeSinceLastBounce[i] = millis();
            Height[i] = StartHeight;
            Position[i] = 0;
            ImpactVelocity[i] = ImpactVelocityStart;
            TimeSinceLastBounce[i] = 0;
            Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        }
        m_BallCount = BallCount;
    }

    for (int i = 0; i < BallCount; i++) {
        TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
        Height[i] =
            0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

        if (Height[i] < 0) {
            Height[i] = 0;
            ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
            ClockTimeSinceLastBounce[i] = millis();

            if (ImpactVelocity[i] < 0.01) {
                ImpactVelocity[i] = ImpactVelocityStart;
            }
        }
        Position[i] = round(Height[i] * (LED_STRIP_LEDSNUM - 1) / StartHeight);
    }

    for (int i = 0; i < BallCount; i++) {
        setPixel(Position[i], colors[i][0], colors[i][1], colors[i][2]);

        showStrip();
        setAll(0, 0, 0);
    }
}

void Led::BouncingBalls()
{
    DEF_COLOR

    int BallCount = args["BallCount"];

    float Gravity = -9.81;
    int StartHeight = 1;

    static float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);

    static float *Height;
    static float *ImpactVelocity;
    static float *TimeSinceLastBounce;
    static int *Position;
    static long *ClockTimeSinceLastBounce;
    static float *Dampening;

    static int m_BallCount = 0;

    if (m_BallCount != BallCount) {
        if (m_BallCount) {
            free(Height);
            free(ImpactVelocity);
            free(TimeSinceLastBounce);
            free(Position);
            free(ClockTimeSinceLastBounce);
            free(Dampening);
        }

        Height = (float *)malloc(sizeof(float) * BallCount);
        ImpactVelocity = (float *)malloc(sizeof(float) * BallCount);
        TimeSinceLastBounce = (float *)malloc(sizeof(float) * BallCount);
        Position = (int *)malloc(sizeof(float) * BallCount);
        ClockTimeSinceLastBounce = (long *)malloc(sizeof(float) * BallCount);
        Dampening = (float *)malloc(sizeof(float) * BallCount);

        for (int i = 0; i < BallCount; i++) {
            ClockTimeSinceLastBounce[i] = millis();
            Height[i] = StartHeight;
            Position[i] = 0;
            ImpactVelocity[i] = ImpactVelocityStart;
            TimeSinceLastBounce[i] = 0;
            Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        }
        m_BallCount = BallCount;
    }

    for (int i = 0; i < BallCount; i++) {
        TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
        Height[i] =
            0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

        if (Height[i] < 0) {
            Height[i] = 0;
            ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
            ClockTimeSinceLastBounce[i] = millis();

            if (ImpactVelocity[i] < 0.01) {
                ImpactVelocity[i] = ImpactVelocityStart;
            }
        }
        Position[i] = round(Height[i] * (LED_STRIP_LEDSNUM - 1) / StartHeight);
    }

    for (int i = 0; i < BallCount; i++) {
        setPixel(Position[i], red, green, blue);
    }

    showStrip();
    setAll(0, 0, 0);
}

void Led::ColorWipe()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR

    int SpeedDelay = args["SpeedDelay"];

    int i = m_theme_state;
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);

    m_theme_state++;
    if (m_theme_state >= LED_STRIP_LEDSNUM)
        m_theme_state = 0;
}

void Led::CylonBounce()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int EyeSize = args["EyeSize"];
    int SpeedDelay = args["SpeedDelay"];
    int ReturnDelay = args["ReturnDelay"];

    static uint16_t i = 0;
    static int phase = 0;

    if (m_theme_state == 0) {
        if (i >= LED_STRIP_LEDSNUM - EyeSize - 2) {
            phase = !phase;
            delay(ReturnDelay);
            i = 0;
            return;
        }
        m_theme_state = 1;
    }

    if (phase == 0) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    } else {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }
    m_theme_state = 0;
}

void Led::FadeInOut()
{
    DEF_COLOR
    float r, g, b;

    for (int k = 0; k < 256; k = k + 1) {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
    }

    for (int k = 255; k >= 0; k = k - 2) {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
    }
}

void Led::Fire()
{
    if (!delay_is_finished())
        return;

    auto setPixelHeatColor = [&](int Pixel, byte temperature) {
        // Scale 'heat' down from 0-255 to 0-191
        byte t192 = round((temperature / 255.0) * 191);

        // calculate ramp up from
        byte heatramp = t192 & 0x3F; // 0..63
        heatramp <<= 2;              // scale up to 0..252

        // figure out which third of the spectrum we're in:
        if (t192 > 0x80) { // hottest
            setPixel(Pixel, 255, 255, heatramp);
        } else if (t192 > 0x40) { // middle
            setPixel(Pixel, 255, heatramp, 0);
        } else { // coolest
            setPixel(Pixel, heatramp, 0, 0);
        }
    };
    static byte heat[LED_STRIP_LEDSNUM];
    int cooldown;

    DEF_COLOR

    int Cooling = args["Cooling"];
    int Sparking = args["Sparkling"];
    int SpeedDelay = args["SpeedDelay"];

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < LED_STRIP_LEDSNUM; i++) {
        cooldown = random(0, ((Cooling * 10) / LED_STRIP_LEDSNUM) + 2);

        if (cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i] - cooldown;
        }
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = LED_STRIP_LEDSNUM - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if (random(255) < Sparking) {
        int y = random(7);
        heat[y] = heat[y] + random(160, 255);
        // heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for (int j = 0; j < LED_STRIP_LEDSNUM; j++) {
        setPixelHeatColor(j, heat[j]);
    }

    showStrip();
    delay(SpeedDelay);
}

void Led::HalloweenEyes()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int EyeWidth = args["EyeWidth"];
    int EyeSpace = args["EyeSpace"];
    boolean Fade = args["Fade"];
    int Steps = random(5, 50);
    int FadeDelay = random(50, 150);
    int EndPause = random(1000, 10000);
    int i;

    static int StartPoint;
    static int Start2ndEye;

    if (m_theme_state == 0) {
        randomSeed(analogRead(0));

        StartPoint = random(0, LED_STRIP_LEDSNUM - (2 * EyeWidth) - EyeSpace);
        Start2ndEye = StartPoint + EyeWidth + EyeSpace;

        for (i = 0; i < EyeWidth; i++) {
            setPixel(StartPoint + i, red, green, blue);
            setPixel(Start2ndEye + i, red, green, blue);
        }

        showStrip();
        delay(FadeDelay);
        return;
    } else if (m_theme_state < Steps + 1) {
        int j = m_theme_state - 1;

        if (Fade == true) {
            float r, g, b;

            r = j * (red / Steps);
            g = j * (green / Steps);
            b = j * (blue / Steps);

            for (i = 0; i < EyeWidth; i++) {
                setPixel(StartPoint + i, r, g, b);
                setPixel(Start2ndEye + i, r, g, b);
            }

            showStrip();
            delay(FadeDelay);
        }
    } else {
        setAll(0, 0, 0); // Set all black
        delay(EndPause);
    }

    m_theme_state++;
    if (m_theme_state > Steps + 2)
        m_theme_state = 0;
}

void Led::RainbowCycle()
{
    if (!delay_is_finished())
        return;

    auto Wheel = [](byte WheelPos) {
        static byte c[3];

        if (WheelPos < 85) {
            c[0] = WheelPos * 3;
            c[1] = 255 - WheelPos * 3;
            c[2] = 0;
        } else if (WheelPos < 170) {
            WheelPos -= 85;
            c[0] = 255 - WheelPos * 3;
            c[1] = 0;
            c[2] = WheelPos * 3;
        } else {
            WheelPos -= 170;
            c[0] = 0;
            c[1] = WheelPos * 3;
            c[2] = 255 - WheelPos * 3;
        }

        return c;
    };

    DEF_COLOR
    int SpeedDelay = args["SpeedDelay"];

    byte *c;
    uint16_t i;

    int j = m_theme_state;

    for (i = 0; i < LED_STRIP_LEDSNUM; i++) {
        c = Wheel(((i * 256 / LED_STRIP_LEDSNUM) + j) & 255);
        setPixel(i, *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);

    m_theme_state++;
    if (m_theme_state == 256 * 5)
        m_theme_state = 0;
}

void Led::TwinkleRandom()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int SpeedDelay = args["SpeedDelay"];
    boolean OnlyOne = args["OnlyOne"];

    setPixel(random(LED_STRIP_LEDSNUM), random(0, 255), random(0, 255), random(0, 255));
    showStrip();
    delay(SpeedDelay);
    if (OnlyOne) {
        setAll(0, 0, 0);
    }
}

void Led::RunningLights()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int WaveDelay = args["WaveDelay"];

    int Position = 0;

    int i = m_theme_state;

    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < LED_STRIP_LEDSNUM; i++) {
        // sine wave, 3 offset waves make a rainbow!
        // float level = sin(i+Position) * 127 + 128;
        // setPixel(i,level,0,0);
        // float level = sin(i+Position) * 127 + 128;
        setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red, ((sin(i + Position) * 127 + 128) / 255) * green,
                 ((sin(i + Position) * 127 + 128) / 255) * blue);
    }

    showStrip();
    delay(WaveDelay);

    m_theme_state++;
    if (m_theme_state == LED_STRIP_LEDSNUM)
        m_theme_state = 0;
}

void Led::SnowSparkle()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int SparkleDelay = args["SparkleDelay"];
    int SpeedDelay = random(100, 1000);

    setAll(red, green, blue);

    int theme_state = m_theme_state;

    if (theme_state == 0) {
        int Pixel = random(LED_STRIP_LEDSNUM);
        m_theme_state = Pixel;
        setPixel(Pixel, 0xff, 0xff, 0xff);
        showStrip();
        delay(SparkleDelay);
    } else {
        int Pixel = m_theme_state;
        setPixel(Pixel, red, green, blue);
        showStrip();
        delay(SpeedDelay);
        m_theme_state = 0;
    }
}

void Led::Sparkle()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int SpeedDelay = args["SpeedDelay"];

    int Pixel = random(LED_STRIP_LEDSNUM);
    setPixel(Pixel, red, green, blue);
    showStrip();
    delay(SpeedDelay);
    setPixel(Pixel, 0, 0, 0);
}

void Led::Strobe()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int EndPause = args["EndPause"];
    int FlashDelay = args["FlashDelay"];
    int StrobeCount = args["StrobeCount"];

    bool show = m_theme_state % 1000;
    int i = m_theme_state / 1000;

    if (i < StrobeCount + 1) {
        if (show) {
            i++;
            setAll(red, green, blue);
        } else {
            setAll(0, 0, 0);
        }
        show = !show;
        showStrip();
        delay(EndPause);
        m_theme_state = i * 1000 + show;
        return;
    }

    setAll(0, 0, 0);
    showStrip();
    delay(FlashDelay);
    m_theme_state = 0;
}

void Led::TheaterChaseRainbow()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int SpeedDelay = args["SpeedDelay"];

    auto Wheel = [](byte WheelPos) {
        static byte c[3];

        if (WheelPos < 85) {
            c[0] = WheelPos * 3;
            c[1] = 255 - WheelPos * 3;
            c[2] = 0;
        } else if (WheelPos < 170) {
            WheelPos -= 85;
            c[0] = 255 - WheelPos * 3;
            c[1] = 0;
            c[2] = WheelPos * 3;
        } else {
            WheelPos -= 170;
            c[0] = 0;
            c[1] = WheelPos * 3;
            c[2] = 255 - WheelPos * 3;
        }

        return c;
    };

    byte *c;

    int j = m_theme_state / 1000;
    int q = m_theme_state % 1000;

    for (int i = 0; i < LED_STRIP_LEDSNUM; i = i + 3) {
        c = Wheel((i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
    }
    showStrip();

    delay(SpeedDelay);

    for (int i = 0; i < LED_STRIP_LEDSNUM; i = i + 3) {
        setPixel(i + q, 0, 0, 0); // turn every third pixel off
    }

    q++;

    if (q == 3) {
        q = 0;
        j++;
    }

    if (j == 256)
        j = 0;

    m_theme_state = j * 1000 + q;
}

void Led::TheaterChase()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int SpeedDelay = args["SpeedDelay"];

    int j = m_theme_state / 1000;
    int q = m_theme_state % 1000;

    for (int i = 0; i < LED_STRIP_LEDSNUM; i = i + 3) {
        setPixel(i + q, red, green, blue); // turn every third pixel on
    }
    showStrip();

    delay(SpeedDelay);

    for (int i = 0; i < LED_STRIP_LEDSNUM; i = i + 3) {
        setPixel(i + q, 0, 0, 0); // turn every third pixel off
    }

    q++;

    if (q == 3) {
        q = 0;
        j++;
    }

    if (j == 10)
        j = 0;

    m_theme_state = j * 1000 + q;
}

void Led::Twinkle()
{
    if (!delay_is_finished())
        return;

    DEF_COLOR
    int Count = args["Count"];
    int SpeedDelay = args["SpeedDelay"];
    int OnlyOne = args["OnlyOne"];

    setAll(0, 0, 0);

    int i = m_theme_state;

    setPixel(random(LED_STRIP_LEDSNUM), red, green, blue);
    showStrip();
    delay(SpeedDelay);
    if (OnlyOne) {
        setAll(0, 0, 0);
    }

    m_theme_state++;
    if (m_theme_state == Count)
        m_theme_state = 0;
}
