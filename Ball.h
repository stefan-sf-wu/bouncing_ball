#ifndef BALL_H_
#define BALL_H_

#ifndef EDGE_SIZE
#define EDGE_SIZE 50
#endif

#include <vector>
#include "Common.h"

class Ball {
public:
    Ball() {
        reset();
    }

    void reset() {
        state_.position = {0.0, 0.0, 0.0};
        state_.velocity = {0.0, 0.0, 0.0};
    }

    struct state getState() {
        return state_;
    }

    int setPosition(float x, float y, float z) {
        if (x < 0 || x >= EDGE_SIZE ||
            y < 0 || y >= EDGE_SIZE ||
            z < 0 || z >= EDGE_SIZE) {
            std::cout << "error: given postion is outside the box.\n";
        }
        state_.position = {x, y, z};
    }

    int setVelocity(float x, float y, float z) {
        state_.velocity = {x, y, z};
    }

private:
    struct state state_;
};

#endif // BALL_H_