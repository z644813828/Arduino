#ifndef MOTION_H
#define MOTION_H

class Motion {
  public:
    static Motion &Instance();

    Motion() {}
    Motion(Motion const &) = delete;
    void operator=(Motion const &) = delete;

    void setup();
    void loop();
    bool getData() { return m_data; };

    void setTimeout(int t)
    {
        if (t < 5)
            t = 5;
        m_timeout = t;
    }
    int getTimeout() { return m_timeout + 5; }

  private:
    void set(bool data);

    bool m_data = false;
    int m_time = 0;
    int m_timeout = 0; // +5 secs from pir module
};

#endif
