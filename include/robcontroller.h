#ifndef __rc_CONTROLLER_H__
#define __rc_CONTROLLER_H__

#include "plcmodel.h"

#define RC_TASK_NAME "rc_task"
#define RC_TASK_PRIORITY 91

/* TODO Add multiple axis ?? */
typedef struct {
    double command_pos;
    double command_vel;
    double command_acc;
    double actual_pos;
    double actual_vel;
    double actual_acc;
} InterpData; /* Single axis interpolation command & actual data from RC */


//static void interp_input_update();
//static void interp_output_update();
static void interp_calculate(void *config); /* TODO NOTE single/multiple axis interpolation */
static void rc_task_create();
void rc_task_init(RobotConfig *config);
void rc_task_start(RobotConfig *config);
void rc_task_delete();
#endif
