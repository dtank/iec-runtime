#ifndef __SERVO_CONTROLLER_H__
#define __SERVO_CONTROLLER_H__

#include "plcmodel.h"

#define SERVO_TASK_NAME "servo_task"
#define SERVO_TASK_PRIORITY 98
typedef struct {
    double actual_pos;
    double actual_vel;
    double actual_acc;
    double command_pos;
    double command_vel;
    double command_acc;
} AXIS_DATA; /* Axis Runtime Data */


static void servo_update(void *config);
static void servo_task_create();
void servo_task_init(SERVO_CONFIG *config);
void servo_task_start(SERVO_CONFIG *config);
void servo_task_delete();
#endif
