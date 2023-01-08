// https://electropeak.com/learn/the-beginners-guide-to-display-text-image-animation-on-oled-display-by-arduino/
// https://www.instructables.com/How-to-Display-Images-on-OLED-Using-Arduino/
// https://blog.hau.me/2018/12/26/i2c-oled-display-on-a-wemos-d1-mini/
// https://www.instructables.com/Wemos-D1-Mini-096-SSD1306-OLED-Display-Using-SPI/

#include "display.h"

#define DISPLAY_DISABLED

Display::Display()
    : m_display(0x3C, D2, D5)
{
#ifdef DISPLAY_DISABLED
    Serial.println("Error: Display::Display() DISABLED !!!");
    return;
#endif
    m_display.init();
    m_display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    // display.flipScreenVertically();

    m_next_update_time = millis();

    memset(&m_monit, 0, sizeof(Status));
    memset(&m_wifi, 0, sizeof(Status));
    memset(&m_mqtt, 0, sizeof(Status));
    memset(&m_soil_wetness, 0, sizeof(Status));
    memset(&m_power, 0, sizeof(Status));
    memset(&m_logo34, 0, sizeof(Status));
    memset(&m_logo68, 0, sizeof(Status));

    // top navbar
    m_wifi.x = 0;
    m_wifi.y = 2;
    m_wifi.img = Signal816;
    m_wifi.width = 16;
    m_wifi.height = 8;

    m_mqtt.x = 24;
    m_mqtt.y = 2;
    m_mqtt.img = Bluetooth88;
    m_mqtt.width = 8;
    m_mqtt.height = 8;

    m_monit.x = 64;
    m_monit.y = 2;
    m_monit.img = Msg816;
    m_monit.width = 16;
    m_monit.height = 8;

    m_soil_wetness.x = 88;
    m_soil_wetness.y = 2;
    m_soil_wetness.img = epd_bitmap_leeve;
    m_soil_wetness.width = 8;
    m_soil_wetness.height = 8;

    m_power.status = true;
    m_power.x = 112;
    m_power.y = 2;
    m_power.img = Bat816;
    m_power.width = 16;
    m_power.height = 8;

    // main icon
    m_logo68.status = true;
    m_logo68.x = (WIDTH - 68) / 2;
    m_logo68.y = (HEIGHT - 8) / 2;
    m_logo68.img = epd_bitmap_rog;
    m_logo68.width = 68;
    m_logo68.height = 34;

    m_logo34.x = (WIDTH - 34) / 2;
    m_logo68.y = (HEIGHT - 8) / 2;
    m_logo34.img = epd_bitmap_rog;
    m_logo34.width = 34;
    m_logo34.height = 34;
}

Display &Display::Instance()
{
    static Display instance;
    return instance;
}

void Display::setMonitText(String text)
{
    m_monit.status = text.isEmpty();
    m_monit.text = text;
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

void Display::render(Status *s)
{
    if (s->status) {
        m_display.drawFastImage(s->x, s->y, s->width, s->height, s->img);
    } else {
        // convert (8*8 || 16*8) -> (34*34 || 68*34)
        Status *logo = s->width == 8 ? &m_logo34 : &m_logo68;

        m_display.drawFastImage(logo->x, logo->y, logo->width, logo->height, s->img);

        if (!s->text.isEmpty())
            m_display.drawString(WIDTH / 2, HEIGHT - 3, s->text);

        if (s->shown)
            m_display.drawFastImage(s->x, s->y, s->width, s->height, s->img);
        s->shown = !s->shown;
    }
}

void Display::loop()
{
#ifdef DISPLAY_DISABLED
    return;
#endif

    if (millis() < m_next_update_time)
        return;

    m_next_update_time += 200;

    m_display.clear();

    render(&m_logo68);
    render(&m_wifi);
    render(&m_mqtt);
    render(&m_monit);
    render(&m_power);

    m_display.display();
}
