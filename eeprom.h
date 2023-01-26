#ifndef EEPROM_H
#define EEPROM_H

#define ARG_LEN 25

#include <Arduino.h>

class Eeprom {
  public:
    static void setup();

    static void save();
    static void load();

    struct Data {
        char color[ARG_LEN];
        char effect[ARG_LEN];
        char error_effect[ARG_LEN];
        int effect_arg[3];
        int brightness;
        int soil_wetness;
        int motion_timeout;
        int display_brightness;
        int display_off_brightness;

        void println()
        {
            Serial.print("color => ");
            Serial.println(color);
            Serial.print("effect => ");
            Serial.println(effect);
            Serial.print("error_effect => ");
            Serial.println(error_effect);
            Serial.print("effect_arg => {");
            Serial.print(effect_arg[0]);
            Serial.print(", ");
            Serial.print(effect_arg[1]);
            Serial.print(", ");
            Serial.print(effect_arg[2]);
            Serial.println("}");
            Serial.print("brightness => ");
            Serial.println(brightness);
            Serial.print("soil_wetness => ");
            Serial.println(soil_wetness);
            Serial.print("motion_timeout => ");
            Serial.println(motion_timeout);
            Serial.print("display_brightness => ");
            Serial.println(display_brightness);
            Serial.print("display_off_brightness => ");
            Serial.println(display_off_brightness);
        }
    };
};

#endif
