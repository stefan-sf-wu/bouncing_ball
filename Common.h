#ifndef COMMON_H_
#define COMMON_H_

#define EDGE_SIZE 150
#define RENDER_RATE 30

#include <vector>

struct vec {
    float x;
    float y;
    float z;
};

struct state {
    struct vec position;
    struct vec velocity;
};


#endif // COMMON_H_