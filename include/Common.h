#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "Bouncing Ball"
#define ENABLE_LOGGER true

/**
 * OBJECT PARAMS
 */ 
#define EDGE_SIZE 24.0         
#define BALL_MASS 0.5   //kg

/**
 * CRONO
 */
#define TIMESTEP 10.0               // millisec
#define MAX_DISPLAY_TIME 30000      // millisec

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1000
#define DISPLAY_REFRESH_INTERVAL (1.0 / 30.0 * 1000.0) // 60 HZ in millisec

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
const double k_airres_coef = 0.05;
const double k_friction_coef = 0.25;
const double k_simplified_friction_coef = 0.2;
const double k_restitution_coef = 0.8;
const struct vec k_gravity = {0, 0, -10};
const struct vec k_wind_velocity = {0, 0, 0};


#endif // COMMON_H_