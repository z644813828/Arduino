// https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/
// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#FastLEDFramework

// #define FASTLED_ALL_PINS_HARDWARE_SPI
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER

#define DEBUG_LED

#include "led.h"

Led &Led::Instance()
{
    static Led instance;
    return instance;
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
    I("CylonBounce", {{"EyeSize", 4}, {"SpeedDelay", 10}, {"ReturnDelay", 15}});
    I("Fire", {{"Cooling", 55}, {"Sparking", 120}, {"SpeedDelay", 15}});
    I("HalloweenEyes", {{"EyeWidth", 1}, {"EyeSpace", 4}, {"Fade", true}});
    I("NewKITT", {{"EyeSize", 8}, {"SpeedDelay", 10}, {"ReturnDelay", 50}});
    I("RainbowCycle", {{"SpeedDelay", 20}});
    I("TwinkleRandom", {{"Count", 20}, {" SpeedDelay", 100}, {"OnlyOne", 0}});
    I("RunningLights", {{"WaveDelay", 50}});
    I("SnowSparkle", {{"SparkleDelay", 20}});
    I("Sparkle", {{"SpeedDelay", 0}});
    I("Strobe", {{"StrobeCount", 10}, {" FlashDelay", 50}, {" EndPause", 1000}});
    I("TheaterChaseRainbow", {{"SpeedDelay", 50}});
    I("TheaterChase", {{"SpeedDelay", 50}});
    I("Twinkle", {{"Count", 10}, {"SpeedDelay", 100}, {"OnlyOne", false}});
}

void Led::setup()
{
    FastLED.addLeds<WS2812, LED_PIN, GRB>(m_strip, LED_NUM);
    FastLED.setBrightness(255);
    fillColorMap();
    fillEffectsMap();
}

void Led::loop()
{
    if (!m_enabled)
        return;

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
        } else if (effect == "NewKITT") {
            NewKITT();
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

    FastLED.setBrightness(m_brightness);

    if (m_error_code)
        exec(m_error_effect);
    else
        exec(m_effect);
}

void Led::setBrightness(int b)
{
    FastLED.setBrightness(b);
    m_brightness = b;
    showStrip();
}

void Led::setErrorCode(int code)
{
    m_error_code = code;
}

void Led::setEnabled(bool e)
{
    m_enabled = e;
    FastLED.setBrightness(e ? m_brightness : 0);
    showStrip();
}

void Led::setColor(String color_in)
{
    m_color_str = color_in;
    m_color = m_color_map[m_color_str];
}

void Led::setEffect(String color_in)
{
    m_effect = color_in;
}

void Led::setErrorEffect(String color_in)
{
    m_error_effect = color_in;
}

void Led::setEffectArg(int idx, String arg)
{
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
    effect->second.insert(std::pair<String, int>(it->first, arg.toInt()));
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

String Led::getHtmlEffectsP(const String &current)
{
    String str;

    std::map<String, std::map<String, int>>::iterator it = m_effect_map.begin();
    while (it != m_effect_map.end()) {
        String effect = it->first;
        str += "    <option value=\"";
        str += effect;
        str += "\"";
        if (effect == current)
            str += " selected";
        str += ">";
        str += effect;
        str += "</option>\n";
        it++;
    }

    return str;
}
String Led::getHtmlEffects()
{
    return getHtmlEffectsP(m_effect);
}

String Led::getHtmlErrorEffects()
{
    return getHtmlEffectsP(m_error_effect);
}

String Led::getHtmlArguments()
{
    String str;

    int i = 0;
    auto effect = m_effect_map.find(m_effect);

    if (effect == m_effect_map.end())
        return str;

    auto effect_data = effect->second;

    std::map<String, int>::iterator it = effect_data.begin();
    while (it != effect_data.end()) {
        String key = it->first;
        String value = String(it->second);
        // clang-format off
        str += R"(
            <form class="d-flex" action="/get">
				<button class="btn btn-light" type="submit">Set</button>
                <div class="input-group mx-2">
                    <div class="input-group-prepend">
                        <span class="input-group-text" id="basic-addon1">)" + key + R"(</span>
                    </div>
                    <input type="text" class="form-control" aria-describedby="basic-addon1"
                        name="effect_arg_)" + String(i) + R"(" placeholder=")" + value + R"(">
                </div>
            </form>
            )";
            i++;
        // clang-format on
        it++;
    }
    return str;
}

void Led::showStrip()
{
    if (m_debug) {
        for (int i = 0; i < LED_NUM; i++) {
            if (!m_strip[i].r && !m_strip[i].g && !m_strip[i].b)
                Serial.print(" ");
            else if (FastLED.getBrightness())
                Serial.print("*");
            else
                Serial.print(" ");
        }
        Serial.print(" ");
        Serial.print(FastLED.getBrightness());
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
    for (int i = 0; i < LED_NUM; i++) {
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
    auto m = eff_data->second; \
    std::vector<int> args; \
    for(std::map<String,int>::iterator it = m.begin(); it != m.end(); ++it) { \
        args.push_back(it->second); \
}
// clang-format on

void Led::StarryNight()
{
    DEF_COLOR

    int Speed = args[0];
    int UnsetTime = args[1];

    for (int i = 0; i < LED_NUM / 10; ++i)
        m_strip[rand() % LED_NUM] = CRGB::White;
    showStrip();

    delay(UnsetTime);

    for (int i = 0; i < LED_NUM; ++i)
        m_strip[i] = m_color;

    int step = 100;
    int b = FastLED.getBrightness() - step + rand() % step;
    FastLED.setBrightness(b);
    showStrip();

    delay(rand() % Speed);

    return;
}

void Led::BouncingColoredBalls()
{
    int BallCount = 3;
    byte colors[3][3];

    DEF_COLOR

    for (int i = 0; i < 3; i++) {
        colors[i][0] = ((args[i] >> 16) & 0xFF);
        colors[i][1] = ((args[i] >> 8) & 0xFF);
        colors[i][2] = ((args[i]) & 0xFF);
    }

    float Gravity = -9.81;
    int StartHeight = 1;

    static float *Height = (float *)malloc(sizeof(float) * BallCount);
    static float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
    static float *ImpactVelocity = (float *)malloc(sizeof(float) * BallCount);
    static float *TimeSinceLastBounce = (float *)malloc(sizeof(float) * BallCount);
    static int *Position = (int *)malloc(sizeof(float) * BallCount);
    static long *ClockTimeSinceLastBounce = (long *)malloc(sizeof(float) * BallCount);
    static float *Dampening = (float *)malloc(sizeof(float) * BallCount);

    static bool initialized = false;

    if (!initialized) {
        for (int i = 0; i < BallCount; i++) {
            ClockTimeSinceLastBounce[i] = millis();
            Height[i] = StartHeight;
            Position[i] = 0;
            ImpactVelocity[i] = ImpactVelocityStart;
            TimeSinceLastBounce[i] = 0;
            Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        }
        initialized = true;
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
        Position[i] = round(Height[i] * (LED_NUM - 1) / StartHeight);
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

    int BallCount = args[0];

    float Gravity = -9.81;
    int StartHeight = 1;

    static float *Height = (float *)malloc(sizeof(float) * BallCount);
    static float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
    static float *ImpactVelocity = (float *)malloc(sizeof(float) * BallCount);
    static float *TimeSinceLastBounce = (float *)malloc(sizeof(float) * BallCount);
    static int *Position = (int *)malloc(sizeof(float) * BallCount);
    static long *ClockTimeSinceLastBounce = (long *)malloc(sizeof(float) * BallCount);
    static float *Dampening = (float *)malloc(sizeof(float) * BallCount);

    static bool initialized = false;

    if (!initialized) {
        for (int i = 0; i < BallCount; i++) {
            ClockTimeSinceLastBounce[i] = millis();
            Height[i] = StartHeight;
            Position[i] = 0;
            ImpactVelocity[i] = ImpactVelocityStart;
            TimeSinceLastBounce[i] = 0;
            Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        }
        initialized = true;
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
        Position[i] = round(Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for (int i = 0; i < BallCount; i++) {
        setPixel(Position[i], red, green, blue);
    }

    showStrip();
    setAll(0, 0, 0);
}

void Led::ColorWipe()
{
    DEF_COLOR

    int SpeedDelay = args[0];

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        setPixel(i, red, green, blue);
        showStrip();
        delay(SpeedDelay);
    }
}

void Led::CylonBounce()
{
    DEF_COLOR
    int EyeSize = args[0];
    int SpeedDelay = args[1];
    int ReturnDelay = args[2];

    for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);

    for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
        setAll(0, 0, 0);
        setPixel(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++) {
            setPixel(i + j, red, green, blue);
        }
        setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        showStrip();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);
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
    static byte heat[NUM_LEDS];
    int cooldown;

    DEF_COLOR

    int Cooling = args[0];
    int Sparking = args[1];
    int SpeedDelay = args[2];

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++) {
        cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

        if (cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i] - cooldown;
        }
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = NUM_LEDS - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if (random(255) < Sparking) {
        int y = random(7);
        heat[y] = heat[y] + random(160, 255);
        // heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for (int j = 0; j < NUM_LEDS; j++) {
        setPixelHeatColor(j, heat[j]);
    }

    showStrip();
    delay(SpeedDelay);
}

void Led::HalloweenEyes()
{
    DEF_COLOR
    int EyeWidth = args[0];
    int EyeSpace = args[1];
    boolean Fade = args[2];
    int Steps = random(5, 50);
    int FadeDelay = random(50, 150);
    int EndPause = random(1000, 10000);

    randomSeed(analogRead(0));

    int i;
    int StartPoint = random(0, NUM_LEDS - (2 * EyeWidth) - EyeSpace);
    int Start2ndEye = StartPoint + EyeWidth + EyeSpace;

    for (i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, red, green, blue);
        setPixel(Start2ndEye + i, red, green, blue);
    }

    showStrip();

    if (Fade == true) {
        float r, g, b;

        for (int j = Steps; j >= 0; j--) {
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
    }

    setAll(0, 0, 0); // Set all black

    delay(EndPause);
}

void Led::NewKITT()
{
    DEF_COLOR
    int EyeSize = args[0];
    int SpeedDelay = args[1];
    int ReturnDelay = args[2];

    auto CenterToOutside = [&]() {
        for (int i = ((NUM_LEDS - EyeSize) / 2); i >= 0; i--) {
            setAll(0, 0, 0);

            setPixel(i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(i + j, red, green, blue);
            }
            setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

            setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(NUM_LEDS - i - j, red, green, blue);
            }
            setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

            showStrip();
            delay(SpeedDelay);
        }
        delay(ReturnDelay);
    };

    auto OutsideToCenter = [&]() {
        for (int i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
            setAll(0, 0, 0);

            setPixel(i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(i + j, red, green, blue);
            }
            setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

            setPixel(NUM_LEDS - i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(NUM_LEDS - i - j, red, green, blue);
            }
            setPixel(NUM_LEDS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

            showStrip();
            delay(SpeedDelay);
        }
        delay(ReturnDelay);
    };

    auto LeftToRight = [&]() {
        for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
            setAll(0, 0, 0);
            setPixel(i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(i + j, red, green, blue);
            }
            setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
            showStrip();
            delay(SpeedDelay);
        }
        delay(ReturnDelay);
    };

    auto RightToLeft = [&]() {
        for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
            setAll(0, 0, 0);
            setPixel(i, red / 10, green / 10, blue / 10);
            for (int j = 1; j <= EyeSize; j++) {
                setPixel(i + j, red, green, blue);
            }
            setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
            showStrip();
            delay(SpeedDelay);
        }
        delay(ReturnDelay);
    };

    RightToLeft();
    LeftToRight();
    OutsideToCenter();
    CenterToOutside();
    LeftToRight();
    RightToLeft();
    OutsideToCenter();
    CenterToOutside();
}

void Led::RainbowCycle()
{
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
    int SpeedDelay = args[0];

    byte *c;
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        for (i = 0; i < NUM_LEDS; i++) {
            c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
            setPixel(i, *c, *(c + 1), *(c + 2));
        }
        showStrip();
        delay(SpeedDelay);
    }
}

void Led::TwinkleRandom()
{
    DEF_COLOR
    int Count = args[0];
    int SpeedDelay = args[1];
    boolean OnlyOne = args[2];

    setAll(0, 0, 0);

    for (int i = 0; i < Count; i++) {
        setPixel(random(NUM_LEDS), random(0, 255), random(0, 255), random(0, 255));
        showStrip();
        delay(SpeedDelay);
        if (OnlyOne) {
            setAll(0, 0, 0);
        }
    }

    delay(SpeedDelay);
}

void Led::RunningLights()
{
    DEF_COLOR
    int WaveDelay = args[0];

    int Position = 0;

    for (int i = 0; i < NUM_LEDS * 2; i++) {
        Position++; // = 0; //Position + Rate;
        for (int i = 0; i < NUM_LEDS; i++) {
            // sine wave, 3 offset waves make a rainbow!
            // float level = sin(i+Position) * 127 + 128;
            // setPixel(i,level,0,0);
            // float level = sin(i+Position) * 127 + 128;
            setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red, ((sin(i + Position) * 127 + 128) / 255) * green,
                     ((sin(i + Position) * 127 + 128) / 255) * blue);
        }

        showStrip();
        delay(WaveDelay);
    }
}

void Led::SnowSparkle()
{
    DEF_COLOR
    int SparkleDelay = args[0];
    int SpeedDelay = random(100, 1000);

    setAll(red, green, blue);

    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, 0xff, 0xff, 0xff);
    showStrip();
    delay(SparkleDelay);
    setPixel(Pixel, red, green, blue);
    showStrip();
    delay(SpeedDelay);
}

void Led::Sparkle()
{
    DEF_COLOR
    int SpeedDelay = args[0];

    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, red, green, blue);
    showStrip();
    delay(SpeedDelay);
    setPixel(Pixel, 0, 0, 0);
}

void Led::Strobe()
{
    DEF_COLOR
    int StrobeCount = args[0];
    int FlashDelay = args[1];
    int EndPause = args[2];

    for (int j = 0; j < StrobeCount; j++) {
        setAll(red, green, blue);
        showStrip();
        delay(FlashDelay);
        setAll(0, 0, 0);
        showStrip();
        delay(FlashDelay);
    }

    delay(EndPause);
}

void Led::TheaterChaseRainbow()
{
    DEF_COLOR
    int SpeedDelay = args[0];

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

    for (int j = 0; j < 256; j++) { // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                c = Wheel((i + j) % 255);
                setPixel(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            showStrip();

            delay(SpeedDelay);

            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}

void Led::TheaterChase()
{
    DEF_COLOR
    int SpeedDelay = args[0];

    for (int j = 0; j < 10; j++) { // do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, red, green, blue); // turn every third pixel on
            }
            showStrip();

            delay(SpeedDelay);

            for (int i = 0; i < NUM_LEDS; i = i + 3) {
                setPixel(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}

void Led::Twinkle()
{
    DEF_COLOR
    int Count = args[0];
    int SpeedDelay = args[1];
    int OnlyOne = args[2];

    setAll(0, 0, 0);

    for (int i = 0; i < Count; i++) {
        setPixel(random(NUM_LEDS), red, green, blue);
        showStrip();
        delay(SpeedDelay);
        if (OnlyOne) {
            setAll(0, 0, 0);
        }
    }

    delay(SpeedDelay);
}
