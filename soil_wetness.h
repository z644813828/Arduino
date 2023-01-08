#ifndef SOIL_WETNESS_H
#define SOIL_WETNESS_H

class SoilWetness {
  public:
    static SoilWetness &Instance();

    SoilWetness() {}

    SoilWetness(SoilWetness const &) = delete;
    void operator=(SoilWetness const &) = delete;

    void setup() {}
    void loop();
};

#endif
