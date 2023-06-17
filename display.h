#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

struct Status {
    bool shown;
    String text;
    bool status;

    uint8_t x;
    uint8_t y;
    const uint8_t *img;
    const uint8_t *img_full;
    uint8_t width;
    uint8_t height;
};

class Display {
  public:
    static Display &Instance();

    Display();

    Display(Display const &) = delete;
    void operator=(Display const &) = delete;

    void setup();
    void loop();

    void setMonitText(String text);
    void setMqttConnected(bool b);
    void setWifiConnected(bool b);
    void setSoilWetness(bool b);

    void startSelfTest();

    void setEnabled(bool e) { m_enabled = e; };
    void setForceOn(bool e) { m_force_on = e; };
    void setForceOff(bool e) { m_force_off = e; };

    void setBrightness(int b) { m_on_brightness = b; }
    int getBrightness() { return m_on_brightness; }

    void setOffBrightness(int b) { m_off_brightness = b; }
    int getOffBrightness() { return m_off_brightness; }

  private:
    void render(Status &s);
    void changeBrightness(int brightness);

    Status m_monit;
    Status m_wifi;
    Status m_mqtt;
    Status m_soil_wetness;
    Status m_power;
    Status m_logo34;
    Status m_logo68;

    bool m_logo_printed;
    bool m_text_printed;

    long int m_next_update_time;

    int m_text_pos = 0;

    bool m_enabled = false;
    bool m_force_on = false;
    bool m_force_off = false;

    int m_brightness = 255;
    int m_on_brightness = 255;
    int m_off_brightness = 20;
};

// clang-format off
const unsigned char Rog6834 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xf0, 0x03, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x7f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0,
	0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x7f, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01,
	0xfe, 0x01, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x07, 0xf1, 0xf8, 0x00, 0x00, 0x00,
	0x00, 0x07, 0xf0, 0x3f, 0x87, 0xf8, 0x00, 0x40, 0x00, 0x00, 0x1f, 0xc0, 0xfe, 0x3f, 0xf0, 0x00,
	0x60, 0x00, 0x00, 0x3f, 0x03, 0xf8, 0xff, 0xf0, 0x00, 0x38, 0x00, 0x00, 0x7c, 0x0f, 0xc3, 0xef,
	0xe0, 0x00, 0x38, 0x20, 0x01, 0xf8, 0x3f, 0x1f, 0x0f, 0xc0, 0x00, 0x1c, 0x38, 0x03, 0xe0, 0xfc,
	0x78, 0x1f, 0xc0, 0x00, 0x1f, 0x1e, 0x07, 0xc3, 0xf1, 0xe0, 0x1f, 0x80, 0x00, 0x0f, 0x8f, 0xff,
	0x0f, 0xc7, 0x00, 0x3f, 0x80, 0x00, 0x03, 0xcf, 0xfe, 0x3f, 0x18, 0x00, 0x7f, 0x00, 0x00, 0x00,
	0xe7, 0xf8, 0xfc, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x33, 0xf3, 0xf0, 0x00, 0x01, 0xfc, 0x00,
	0x00, 0x00, 0x03, 0xe7, 0xf0, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xe7, 0xff, 0x00, 0x07,
	0xf8, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0f,
	0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x0c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};

const unsigned char Signal816 [16] PROGMEM = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x50, 0x00, 0xd0, 0x02, 0xd0, 0x06, 0xd0, 0x06, 0xd0, 0x00, 0x00
};
const unsigned char Signal6834 [306] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x43, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf3, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x71, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xf3, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x79, 0xf3, 0xc0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x79, 
	0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0e, 
	0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x1f, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x1f, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3c, 0x79, 0xf3, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3c, 0x79, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3c, 
	0x78, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00
};

const unsigned char Msg816 [16] PROGMEM = {
	0x00, 0x00, 0x0f, 0xf0, 0x0c, 0x30, 0x0a, 0x50, 0x09, 0x90, 0x08, 0x10, 0x0f, 0xf0, 0x00, 0x00
};
const unsigned char Msg6834 [306] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x07, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x0e, 
	0xe0, 0x00, 0x00, 0x00, 0x00, 0x73, 0x80, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x73, 0xc0, 
	0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x71, 0xe0, 0x00, 0x70, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x70, 0xf0, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x78, 0x01, 0xc0, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x70, 0x3c, 0x03, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x1e, 0x07, 0x80, 0xe0, 
	0x00, 0x00, 0x00, 0x00, 0x70, 0x0f, 0x0f, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x07, 0xfe, 
	0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x03, 0xfc, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 
	0x00, 0xf0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00
};

const uint8_t Bat816[16] PROGMEM = {
    0x0F,0xFE,0x30,0x02,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x30,0x02,0x0F,0xFE
};

const unsigned char Server88 [8] PROGMEM = {
	0x7e, 0x50, 0x7e, 0x00, 0x00, 0x7e, 0x50, 0x7e
};
const unsigned char Server3434 [170] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x10, 
	0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x17, 0xf7, 0x00, 0x02, 0x00, 0x15, 0xd5, 
	0x00, 0xaa, 0x00, 0x17, 0x77, 0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x18, 0x00, 0x00, 
	0x06, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x02, 0x00, 0x00, 0x10, 
	0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x13, 0x77, 0x00, 0x02, 0x00, 
	0x15, 0xd5, 0x00, 0x22, 0x00, 0x15, 0xd5, 0x00, 0x22, 0x00, 0x13, 0x77, 0x00, 0x02, 0x00, 0x10, 
	0x00, 0x00, 0x02, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x02, 0x00, 
	0x00, 0x10, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x18, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x00, 
	0x02, 0x00, 0x17, 0x77, 0x00, 0x02, 0x00, 0x15, 0xd5, 0x00, 0xaa, 0x00, 0x17, 0xf7, 0x00, 0x02, 
	0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 
	0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Leeve88 [8] PROGMEM = {
	0x40, 0x66, 0x7e, 0x30, 0x1c, 0x18, 0x10, 0x3c
};
const unsigned char Leeve3434 [170] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x0f, 
	0xe0, 0x00, 0x1c, 0x00, 0x0f, 0xf8, 0x01, 0xfc, 0x00, 0x0f, 0xfc, 0x03, 0xfc, 0x00, 0x0f, 0xfc, 
	0x07, 0xfc, 0x00, 0x0f, 0xfe, 0x0f, 0xfc, 0x00, 0x0f, 0xfe, 0x1f, 0xf8, 0x00, 0x0f, 0xff, 0x1f, 
	0xf8, 0x00, 0x07, 0xff, 0x1f, 0xf0, 0x00, 0x07, 0xff, 0x3f, 0xe0, 0x00, 0x03, 0xff, 0x3f, 0xc0, 
	0x00, 0x01, 0xff, 0x3e, 0x00, 0x00, 0x00, 0xff, 0x40, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 
	0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x01, 0x1f, 0x80, 0x00, 0x00, 
	0x01, 0x3f, 0xc0, 0x00, 0x00, 0x03, 0x7f, 0xc0, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x02, 
	0xff, 0x00, 0x00, 0x00, 0x03, 0x7c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// clang-format on

#endif
