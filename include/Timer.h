#ifndef TIMER_H_
#define TIMER_H_

#include <thread>
#include <unistd.h>
#include <chrono>

#include "Common.h"


class Timer
{
    private:
    std::chrono::time_point<std::chrono::steady_clock> real_time_offset_;
    std::chrono::time_point<std::chrono::steady_clock> real_time_now_;
    long real_time_lapse_;
    long simulation_time_;
    long timestep_;
    long next_display_time_;

    private:
    


    public:
    Timer();
    ~Timer();

    void reset() {
        timestep_               = TIMESTEP;
        simulation_time_        = 0;
        next_display_time_      = simulation_time_ + DISPLAY_REFRESH_INTERVAL;
        real_time_offset_       = std::chrono::steady_clock::now();
    }

    void update_simulation_time(long millisec) {
        simulation_time_ += millisec;
    }

    void update_next_display_time() {
        next_display_time_ += DISPLAY_REFRESH_INTERVAL;
    }

    void calibrate_time() {
        real_time_now_   = std::chrono::steady_clock::now();
        real_time_lapse_ = std::chrono::duration_cast<std::chrono::milliseconds>(real_time_now_ - real_time_offset_).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(simulation_time_- real_time_lapse_));
    }
    
    bool is_time_to_draw() {
        return (simulation_time_ > next_display_time_);
    }

    bool is_time_to_stop() {
        return (simulation_time_ > T_MAX);
    }

#ifdef ENABLE_LOGGER
    void logger() {
        std::cout << "timer class | ";
        std::cout << "[simulation_time_: " << simulation_time_ << "] ";
        std::cout << "[next_display_time_: " << next_display_time_ << "] ";
    }
#endif
};

Timer::Timer() {}
Timer::~Timer() {}
    
#endif
