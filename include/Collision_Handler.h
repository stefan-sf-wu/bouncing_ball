#ifndef COLLISION_HANDLER_H_
#define COLLISION_HANDLER_H_

#include <cmath>

#include "Common.h"
#include "Math.h"

class Collision_Handler {
  private:
    struct plain plain_[6]; 
    struct vec   point_on_plain_[6];
    double distance_curr_;
    double distance_next_;

    double calculate_signed_distance(int idx, struct vec *position) {
        struct vec v = {
            position->x - point_on_plain_[idx].x,
            position->y - point_on_plain_[idx].y,
            position->z - point_on_plain_[idx].z
        };
        struct vec n = {
            plain_[idx].a, 
            plain_[idx].b, 
            plain_[idx].c
        };
        return vec_dot_product(n, v);
    }

  public:
    Collision_Handler();
    ~Collision_Handler();

    void reset() {
        plain_[0] = {1, 0, 0, 0};          // BACK
        plain_[1] = {0, 1, 0, 0};           // LEFT
        plain_[2] = {0, 0, 1, 0};           // BOTTOM
        plain_[3] = {1, 0, 0, -EDGE_SIZE};  // FRONT
        plain_[4] = {0, 1, 0, -EDGE_SIZE};  // RIGHT
        plain_[5] = {0, 0, 1, -EDGE_SIZE};  // TOP

        point_on_plain_[0] = {0, 0, 0};
        point_on_plain_[1] = {0, 0, 0};
        point_on_plain_[2] = {0, 0, 0};
        point_on_plain_[3] = {EDGE_SIZE, EDGE_SIZE, EDGE_SIZE};
        point_on_plain_[4] = {EDGE_SIZE, EDGE_SIZE, EDGE_SIZE};
        point_on_plain_[5] = {EDGE_SIZE, EDGE_SIZE, EDGE_SIZE};
    }

    bool detect_collision(struct vec *position_curr, struct vec *position_next) {
        for(int i = 0; i < 6; i++) {
            distance_curr_ = calculate_signed_distance(i, position_curr);
            distance_next_ = calculate_signed_distance(i, position_next);
            if (std::signbit(distance_curr_) != std::signbit(distance_next_)) {
                return true;
            }
        }
        return false;
    }

    double get_timestep_fraction() {
        return distance_curr_ / (distance_curr_ - distance_next_);
    }
};

Collision_Handler::Collision_Handler() {}
Collision_Handler::~Collision_Handler() {}


#endif // COLLISION_HANDLER_H_