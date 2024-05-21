#include "Time.h"
#include "CommonFunction.h"
Time::Time()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused_ = false;
    is_started_ = false;

}
Time::~Time()
{

}
void Time::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks();
}
void Time::stop()
{
    is_paused_ = false;
   is_started_ = false;
}
void Time::paused()
{
    if (is_started_ == true && is_paused_ == false) {
        is_paused_ = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}
void Time::unpaused()
{
    if (is_paused_ == true) {
        is_paused_ = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}
int Time::get_tick()
{
    if (is_started_ == true) {
        if (is_paused_ == true) {
            return pause_tick;
        }
        else {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}
bool Time::is_started()
{
    return is_started_;
}
bool Time::is_paused()
{
    return is_paused_;
}

