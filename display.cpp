// https://electropeak.com/learn/the-beginners-guide-to-display-text-image-animation-on-oled-display-by-arduino/
// https://www.instructables.com/How-to-Display-Images-on-OLED-Using-Arduino/
// https://blog.hau.me/2018/12/26/i2c-oled-display-on-a-wemos-d1-mini/
// https://www.instructables.com/Wemos-D1-Mini-096-SSD1306-OLED-Display-Using-SPI/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "config.h"
#include "display.h"

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 m_display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

Display::Display()
{
    m_next_update_time = millis();

    // top navbar
    m_wifi.type = "m_wifi";
    m_wifi.x = 0;
    m_wifi.y = 2;
    m_wifi.img = Signal816;
    m_wifi.img_full = Signal6834;
    m_wifi.width = 16;
    m_wifi.height = 8;

    m_mqtt.type = "m_mqtt";
    m_mqtt.x = 32;
    m_mqtt.y = 2;
    m_mqtt.img = Server88;
    m_mqtt.img_full = Server3434;
    m_mqtt.width = 8;
    m_mqtt.height = 8;

    m_monit.type = "m_monit";
    m_monit.status = true;
    m_monit.x = 52;
    m_monit.y = 2;
    m_monit.img = Msg816;
    m_monit.img_full = Msg6834;
    m_monit.width = 16;
    m_monit.height = 8;

    m_soil_wetness.type = "m_soil_wetness";
    m_soil_wetness.x = 88;
    m_soil_wetness.y = 2;
    m_soil_wetness.img = Leeve88;
    m_soil_wetness.img_full = Leeve3434;
    m_soil_wetness.width = 8;
    m_soil_wetness.height = 8;

    m_power.type = "m_power";
    m_power.status = true;
    m_power.x = 112;
    m_power.y = 2;
    m_power.img = Bat816;
    m_power.width = 16;
    m_power.height = 8;

    // main icon
    m_logo68.status = true;
    m_logo68.x = (DISPLAY_WIDTH - 68) / 2;
    m_logo68.y = 16;
    m_logo68.img = Rog6834;
    m_logo68.width = 68;
    m_logo68.height = 34;

    m_logo34.x = (DISPLAY_WIDTH - 34) / 2;
    m_logo34.y = 16;
    m_logo34.img = Rog6834;
    m_logo34.width = 34;
    m_logo34.height = 34;
}

static Display display;
Display &Display::Instance()
{
    return display;
}

void Display::setup()
{
    m_display.begin(SSD1306_SWITCHCAPVCC, GPIO_DISPLAY_PIN);

    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(WHITE);
    m_display.setCursor(0, 0);
    m_display.println(">");
    delay(500);

    m_display.display();
}

void Display::setMonitText(String text)
{
    m_monit.status = text.isEmpty();
    m_monit.text = text;
    m_text_pos = -DISPLAY_LINE_SYMBOLS;
}

void Display::setMqttConnected(bool b)
{
    m_mqtt.status = b;
}

void Display::setWifiConnected(bool b)
{
    m_wifi.status = b;
}

void Display::setSoilWetness(bool b)
{
    m_soil_wetness.status = b;
}

void Display::render(Status &s)
{
    if (s.status) {
        if (s.img)
            m_display.drawBitmap(s.x, s.y, s.img, s.width, s.height, WHITE);
        return;
    }

    if (!m_logo_printed) {
        m_logo_printed = true;
        // convert (8*8 || 16*8) . (34*34 || 68*34)
        Status logo = s.width == 8 ? m_logo34 : m_logo68;
        if (s.img_full)
            m_display.drawBitmap(logo.x, logo.y, s.img_full, logo.width, logo.height, WHITE);
    }

    if (!m_text_printed) {
        m_text_printed = true;
        if (!s.text.isEmpty()) {
            m_display.setTextSize(1);
            m_display.setTextColor(WHITE);
            m_display.setCursor(0, DISPLAY_HEIGHT - 8);
            int pos = (m_text_pos < 0) ? 0 : m_text_pos;
            String str = s.text.substring(pos);
            m_text_pos += 1;
            m_display.println(str);

            if (m_text_pos >= (int(s.text.length()) - DISPLAY_LINE_SYMBOLS)) {
                m_text_pos = -DISPLAY_LINE_SYMBOLS;
            }
        }
    }

    if (s.shown && s.img)
        m_display.drawBitmap(s.x, s.y, s.img, s.width, s.height, WHITE);
    s.shown = !s.shown;
}

void Display::loop()
{
    if (millis() < m_next_update_time)
        return;

    m_next_update_time += 200;

    if (m_force_off) {
        m_display.clearDisplay();
        return;
    }

    bool show = m_enabled || m_force_on;
    m_logo68.status = show;

    changeBrightness(show ? m_on_brightness : m_off_brightness);

    m_display.clearDisplay();
    m_logo_printed = false;
    m_text_printed = false;

    render(m_wifi);
    render(m_mqtt);
    render(m_monit);
    render(m_soil_wetness);
    render(m_power);

    if (!m_logo_printed && show)
        render(m_logo68);

    m_display.display();
}

void Display::startSelfTest()
{
    m_display.clearDisplay();

    Status logo68 = m_logo68;
    Status wifi = m_wifi;
    Status mqtt = m_mqtt;
    Status monit = m_monit;
    Status power = m_power;

    logo68.status = true;
    wifi.status = true;
    mqtt.status = true;
    monit.status = true;
    power.status = true;

    render(logo68);
    render(wifi);
    render(mqtt);
    render(monit);
    render(power);
    m_display.display();
    delay(2000);

    logo68.text = __func__;

    auto test = [&](Status &s) {
        s.status = false;
        m_display.display();
        delay(2000);
    };

    test(logo68);
    test(wifi);
    test(mqtt);
    test(monit);
    test(power);
}

void Display::changeBrightness(int brightness)
{
    if (m_brightness == brightness)
        return;

    m_brightness = brightness;

    int prech;
    int brigh;

    switch (brightness) {
    case 001 ... 255:
        prech = 0;
        brigh = brightness;
        break;
    case 256 ... 411:
        prech = 16;
        brigh = brightness - 156;
        break;
    default:
        prech = 16;
        brigh = 255;
        break;
    }

    m_display.ssd1306_command(SSD1306_SETPRECHARGE);
    m_display.ssd1306_command(prech);
    m_display.ssd1306_command(SSD1306_SETCONTRAST);
    m_display.ssd1306_command(brigh);
}
