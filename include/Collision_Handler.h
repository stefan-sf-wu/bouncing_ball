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
    int    idx_collision_plain_;

    double calculate_signed_distance(int idx, struct vec *position) {
        struct vec v = {
            position->x - point_on_plain_[idx].x,
            position->y - point_on_plain_[idx].y,
            position->z - point_on_plain_[idx].z
        };
        return vec_dot_product(plain_[idx].get_unit_normal(), v);
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
                idx_collision_plain_ = i;
                return true;
            }
        }
        return false;
    }

    double get_timestep_fraction() {
        return distance_curr_ / (distance_curr_ - distance_next_);
    }

    struct vec get_collision_response(struct vec v_collision) {
        struct vec p_normal = plain_[idx_collision_plain_].get_unit_normal();

        struct vec v_in_normal      = vec_multiply(p_normal, 
                                                   vec_dot_product(v_collision, p_normal));
        struct vec v_in_tangential  = vec_substract(v_collision, v_in_normal);
        struct vec v_out_normal     = vec_multiply(v_in_normal, -k_restitution_coef);



        struct vec v_out_tangential = vec_substract(v_in_tangential, 
                                                    vec_multiply(vec_get_unit(v_in_tangential), 
                                                                 std::min(k_friction_coef * vec_get_sqrt(v_in_normal), 
                                                                          vec_get_sqrt(v_in_tangential))));   
#ifdef ENABLE_LOGGER
        std::cout << "v_in_normal: [" << v_in_normal.x << ' ' <<  v_in_normal.y << ' ' << v_in_normal.z << "]\n";
        std::cout << "v_in_tangential: [" << v_in_tangential.x << ' ' <<  v_in_tangential.y << ' ' << v_in_tangential.z << "]\n";
        std::cout << "v_out_normal: [" << v_out_normal.x << ' ' <<  v_out_normal.y << ' ' << v_out_normal.z << "]\n";
        std::cout << "v_out_tangential: [" << v_out_tangential.x << ' ' <<  v_out_tangential.y << ' ' << v_out_tangential.z << "]\n";     
#endif                                        
        return vec_add(v_out_normal, v_out_tangential);
    }
};

Collision_Handler::Collision_Handler() {}
Collision_Handler::~Collision_Handler() {}


#endif // COLLISION_HANDLER_H_