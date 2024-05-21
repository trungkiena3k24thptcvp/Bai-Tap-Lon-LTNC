#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

class Time
{
public:
    Time();
    ~Time();
    void start();
    void stop();
    void paused();
    void unpaused();

    int get_tick();

    bool is_started();
    bool is_paused();
private:
    int start_tick;
    int pause_tick;

    bool is_paused_;
    bool is_started_;

};

#endif // TIME_H_INCLUDED
