#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "Bouncing Ball"
#define ENABLE_LOGGER true

/**
 * CRONO
 */
#define TIMESTEP 10.0               // millisec
#define MAX_DISPLAY_TIME 30000      // millisec

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define DISPLAY_REFRESH_INTERVAL (1.0 / 60.0 * 1000.0) // 60 HZ in millisec


#define EDGE_SIZE 100.0         // even numbers
#define BALL_MASS 0.5
#define AIR_RESIST_CONST 0.01

struct vec {
    double x;
    double y;
    double z;
};

struct plain {
    // a*x + b*y + c*z + d = 0
    double a;
    double b;
    double c;
    double d;
};

struct state {
    struct vec position;
    struct vec velocity;
};


/**
 * FORCE
 */ 
const struct vec k_gravity = {0, 0, -10};
const struct vec k_wind    = {0, 0, 0};




#endif // COMMON_H_