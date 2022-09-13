#ifndef BALL_H_
#define BALL_H_

#include <vector>

#include "Common.h"

class Ball {
  private:
    struct state state_;

  private:
    // inline bool isAbnormalPosition(float x, float y, float z) {
    //     return (x < -EDGE_SIZE || x > EDGE_SIZE ||
    //             y < -EDGE_SIZE || y > EDGE_SIZE ||
    //             z < -EDGE_SIZE || z > EDGE_SIZE);
    // }

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
        // if (isAbnormalPosition(x, y, z)) {
        //     std::cout << "error: given postion is outside the box.\n";
        // }
        state_.position = {x, y, z};
    }

    void set_velocity(float x, float y, float z) {
        state_.velocity = {x, y, z};
    }

};

Ball::Ball() {
}
Ball::~Ball() {
}

#endif // BALL_H_