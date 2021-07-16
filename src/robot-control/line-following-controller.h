#ifndef LINE_FOLLOWING_CONTROLLER
#define LINE_FOLLOWING_CONTROLLER

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <stdint.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "robot-core/reflectance.h"
#include "robot-core/dc-motor-two.h"
#include "utilities/util-vars.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef struct {
    float kp;
    float ki;
    float kd;
} pid_constant_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t lineFollowingController_init(reflectance_t* sensor1,
                                            reflectance_t* sensor2,
                                            dc_motor_two_t* motor1,
                                            dc_motor_two_t* motor2);

robot_status_t lineFollowingController_spinOnce();

pid_constant_t* lineFollowingController_getPidConstants();

uint8_t* lineFollowingController_getMinEffSpeed();

uint8_t* lineFollowingController_getMaxEffSpeed();

uint8_t* lineFollowingController_getTargSpeed();

int16_t* lineFollowingController_getError();

#endif // LINE_FOLLOWING_CONTROLLER