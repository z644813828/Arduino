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

    void setDrySignal(int signal) { m_dry_signal = signal; }
    int getDrySignal() { return m_dry_signal; }

    bool getData() { return m_data; };

  private:
    int m_dry_signal = 230;
    bool m_data = false;
};

#endif
