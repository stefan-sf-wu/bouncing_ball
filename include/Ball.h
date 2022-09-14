#ifndef BALL_H_
#define BALL_H_

#include <vector>
#include <iomanip>

#include "Common.h"

class Ball {
  private:
    struct state state_;

  public:
    Ball();
    ~Ball();

    void reset() {
        state_.position = {0.0, 0.0, 0.0};
        state_.velocity = {0.0, 0.0, 0.0};
    }
    
    struct state getState() {
        return state_;
    }

    void set_position(float x, float y, float z) {
        state_.position = {x, y, z};
    }

    void set_velocity(float x, float y, float z) {
        state_.velocity = {x, y, z};
    }

#ifdef ENABLE_LOGGER
    void logger() {
        std::cout << std::setw(10) << "[ball] ";
        std::cout << "position: ["
                      << state_.position.x << ' '
                      << state_.position.y << ' ' 
                      << state_.position.z << "] ";
        std::cout << "velocity: ["
                      << state_.velocity.x << ' '
                      << state_.velocity.y << ' ' 
                      << state_.velocity.z << "] ";
        std::cout << std::endl;
    }
#endif
};

Ball::Ball() {
}
Ball::~Ball() {
}

#endif // BALL_H_