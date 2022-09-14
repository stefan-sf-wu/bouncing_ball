#ifndef TIMER_H_
#define TIMER_H_

#include <thread>
#include <unistd.h>
#include <chrono>
#include <iomanip>

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

    bool no_need_to_calibrate_;
    int  no_need_to_calibrate_cnt_;
    int  no_need_to_calibrate_limit_ = 100;

  private:
    void test_no_need_to_calibrate(long n) {
        if(n < 0) {
            if(no_need_to_calibrate_cnt_++ > no_need_to_calibrate_limit_) {
                no_need_to_calibrate_ = true;
            }
        }
    }

  public:
    Timer();
    ~Timer();

    void reset() {
        timestep_               = TIMESTEP;
        simulation_time_        = 0;
        next_display_time_      = simulation_time_;
        real_time_offset_       = std::chrono::steady_clock::now();

        no_need_to_calibrate_     = false;
        no_need_to_calibrate_cnt_ = 0;
    }

    void update_simulation_time(long millisec) {
        simulation_time_ += millisec;
    }

    void update_next_display_time() {
        next_display_time_ += DISPLAY_REFRESH_INTERVAL;
    }

    void calibrate_time() {
        if (no_need_to_calibrate_) {
            return;
        }

        real_time_now_   = std::chrono::steady_clock::now();
        real_time_lapse_ = std::chrono::duration_cast<std::chrono::milliseconds>(real_time_now_ - real_time_offset_).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(simulation_time_- real_time_lapse_));

        test_no_need_to_calibrate(simulation_time_- real_time_lapse_);
    }
    
    bool is_time_to_draw() {
        return (simulation_time_ >= next_display_time_);
    }

    bool is_time_to_stop() {
        return (simulation_time_ >= MAX_DISPLAY_TIME);
    }

#ifdef ENABLE_LOGGER
    void logger() {
        std::cout << std::setw(10) << "[timer] ";
        std::cout << "[simulation_time: " << simulation_time_ << "] ";
        std::cout << "[next_display_time: " << next_display_time_ << "] ";
    }
#endif
};

Timer::Timer() {}
Timer::~Timer() {}
    
#endif
