#ifndef COMMON_H_
#define COMMON_H_

#define ENABLE_LOGGER true

#define EDGE_SIZE 150       // even numbers
#define TIMESTEP 10          // millisec
#define T_MAX 30000            // millisec
#define DISPLAY_REFRESH_INTERVAL (1.0 / 60.0 * 1000) // 60 HZ in millisec

struct vec {
    float x;
    float y;
    float z;
};

struct state {
    struct vec position;
    struct vec velocity;
};


namespace force {
    const struct vec gravity = {0, 0, -10};
    const struct vec wind    = {0, 0, 0};
}


#endif // COMMON_H_