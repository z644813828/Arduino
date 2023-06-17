#ifndef FPANEL_H
#define FPANEL_H

#include <Arduino.h>

struct Button {
    int val = 0;
    int timeout = 10;
    unsigned long last_time = 0;
};

class FPanel {
  public:
    static FPanel &Instance();

    FPanel() {}
    FPanel(FPanel const &) = delete;
    void operator=(FPanel const &) = delete;

    void setup();
    void loop();

    void setPowerTimeout(int in) { m_power.timeout = in; }
    int getPowerTimeout() { return m_power.timeout; }

    void setAcknowledgeTimeout(int in) { m_acknowledge.timeout = in; }
    int getAcknowledgeTimeout() { return m_acknowledge.timeout; }

    void setErrorCode(int code) { m_error_code = code; }

    int getPower() { return m_power.val; }
    int getAcknowledge() { return m_acknowledge.val; }

  private:
    bool checkTime(Button &btn);
    void togglePower();
    void toggleAcknowledge();

    Button m_power;
    Button m_acknowledge;

    bool m_led_power_state;
    bool m_led_error_state;
    long int m_next_update_time;
    bool m_error_code = 0;
};

#endif
