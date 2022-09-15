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
        state_.position = {EDGE_SIZE / 2, EDGE_SIZE / 2, EDGE_SIZE - 1};
        state_.velocity = {0.0, 0.0, 0.0};
    }
    
    struct state getState() {
        return state_;
    }

    void set_state(struct state st) {
        state_ = st;
    }

    void set_position(double x, double y, double z) {
        state_.position = {x, y, z};
    }

    void set_position(struct vec v) {
        state_.position = v;
    }

    void set_velocity(double x, double y, double z) {
        state_.velocity = {x, y, z};
    }

    void set_velocity(struct vec v) {
        state_.velocity = v;
    }
    
    struct vec get_transformed_postion_for_render() {
        return {
            ((state_.position.x * 2) / EDGE_SIZE) - 1,
            ((state_.position.y * 2) / EDGE_SIZE) - 1,
            ((state_.position.z * 2) / EDGE_SIZE) - 1
        };
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