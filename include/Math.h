#ifndef MATH_H_
#define MATH_H_

namespace math {
struct vec vec_add(struct vec v1, struct vec v2) {
    struct vec ret = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
    return ret;
}
struct vec vec_substract(struct vec v1, struct vec v2) {
    struct vec ret = {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
    return ret;
}
float vec_dot_product(struct vec v1, struct vec v2) {
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
struct vec vec_multiply(struct vec v1, float n) {
    struct vec ret = {
        v1.x * n,
        v1.y * n,
        v1.z * n
    }
    return ret;
}
struct vec vec_cross_product(struct vec v1, struct vec v2) {
    struct vec ret = {
        (v1.y * v2.z) - (v2.y * v1.z),
        -((v1.x * v2.z) - (v2.x * v1.z)),
        (v1.x * v2.y) - (v2.x * v1.y)
    };
    return ret;
}

} // namespace math

#endif // MATH_H_