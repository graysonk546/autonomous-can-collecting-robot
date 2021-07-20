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
    float           kp;
    float           ki;
    float           kd;
    float           delocalizedGain;
    uint8_t         minEffSpeed;
    uint8_t         maxEffSpeed;
    uint8_t         targetVelocity;
    uint8_t         maxITermMagnitude;
    uint16_t        delocalizedReflectanceThreshold;
    reflectance_t*  reflectanceArr[NUM_LINE_FOLLOWING_SENSORS];
    dc_motor_two_t* motorArr[NUM_DRIVING_MOTORS];
} line_following_controller_config_t;

typedef struct {
    float           pTerm;
    float           iTerm;
    float           dTerm;
    float           controlOutput;
    int16_t         error;
    int16_t         previousError;
    int16_t         leftMotorVelocity;
    int16_t         previousLeftMotorVelocity;
    int16_t         rightMotorVelocity;
    int16_t         previousRightMotorVelocity;
    bool            initialized;
} line_following_controller_state_t;

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

line_following_controller_config_t* lineFollowingController_getConfig();

line_following_controller_state_t* lineFollowingController_getState();

#endif // LINE_FOLLOWING_CONTROLLER