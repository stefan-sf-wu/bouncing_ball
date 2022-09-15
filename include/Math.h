#ifndef MATH_H_
#define MATH_H_

#include <cmath>

#include "Common.h"

struct vec vec_add(struct vec v1, struct vec v2) {
    struct vec ret = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
    return ret;
};

struct vec vec_substract(struct vec v1, struct vec v2) {
    return {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
};

double vec_dot_product(struct vec v1, struct vec v2) {
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

struct vec vec_multiply(struct vec v1, double n) {
    return {
        v1.x *= n,
        v1.y *= n,
        v1.z *= n
    };
};

struct vec vec_cross_product(struct vec v1, struct vec v2) {
    return {
        (v1.y * v2.z) - (v2.y * v1.z),
        -((v1.x * v2.z) - (v2.x * v1.z)),
        (v1.x * v2.y) - (v2.x * v1.y)
    };
};

double vec_get_sqrt(struct vec v) {
    return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2));
}

struct vec vec_get_unit(struct vec v) {
    if(v.x == 0 && v.y == 0 && v.z == 0) {
        return {0, 0, 0};
    }
    double dist = vec_get_sqrt(v);
    return {
        v.x / dist,
        v.y / dist,
        v.z / dist
    };
}


#endif // MATH_H_