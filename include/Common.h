#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "Bouncing Ball"
#define ENABLE_LOGGER true

/**
 * OBJECT PARAMS
 */ 
#define EDGE_SIZE 100.0         // even numbers
#define BALL_MASS 0.5   //kg

/**
 * CRONO
 */
#define TIMESTEP 100.0               // millisec
#define MAX_DISPLAY_TIME 30000      // millisec

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define DISPLAY_REFRESH_INTERVAL (1.0 / 60.0 * 1000.0) // 60 HZ in millisec

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
        
    struct vec get_unit_normal() {
        return {a, b, c};
    }
};

struct state {
    struct vec position;
    struct vec velocity;
};

/**
 * FORCE
 */ 
const double k_air_resistance_coef = 0.01;
const double k_friction_coef = 0.25;
const double k_restitution_coef = 0.8;
const struct vec k_gravity = {0, 0, -10};
const struct vec k_wind    = {0, 0, 0};


#endif // COMMON_H_