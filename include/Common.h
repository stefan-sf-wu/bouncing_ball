#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "Bouncing Ball"

#define ENABLE_LOGGER true

#

#define EDGE_SIZE 50          // even numbers
#define TIMESTEP 100          // millisec
#define MAX_DISPLAY_TIME 30000           // millisec

#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define DISPLAY_REFRESH_INTERVAL (1.0 / 45.0 * 1000) // 60 HZ in millisec

#define K_BALL_MASS 0.5
#define K_AIR 0.01


struct vec {
    float x;
    float y;
    float z;
};

struct state {
    struct vec position;
    struct vec velocity;
};


// force
const struct vec k_gravity = {0, 0, -10};
const struct vec k_wind    = {0, 0, 0};




#endif // COMMON_H_