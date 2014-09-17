#ifndef __ROB_CONTROLLER_H__
#define __ROB_CONTROLLER_H__

#define ROB_TASK_NAME "rob_task"
#define ROB_TASK_PRIORITY 91

/* TODO Add multiple axis */
typedef struct {
    double command_pos;
    double command_vel;
    double command_acc;
} INTERP_OUTPUT; /* Interpolation Output Data from RC */

typedef struct {
    double actual_pos;
    double actual_vel;
    double actual_acc;
} INTERP_INPUT; /* Interpolation Input Data from PLC */

static void interp_input_update();
static void interp_output_update();
static void interp_calculate(); /* TODO NOTE single/multiple axis interpolation */
static void rob_task_create();
void rob_task_init();
void rob_task_start();
void rob_task_delete();
#endif
