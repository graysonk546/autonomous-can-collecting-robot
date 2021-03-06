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
    float           kd;
    uint8_t         minEffSpeed;
    uint8_t         maxEffSpeed;
    uint8_t         targetVelocity;
    uint16_t        delocalizedReflectanceThreshold;
    uint16_t        previousSpinOffset;
    uint16_t        delocalizedErrorMagnitude;
    reflectance_t*  reflectanceArr[NUM_LINE_FOLLOWING_SENSORS];
    dc_motor_two_t* motorArr[NUM_DRIVING_MOTORS];
} line_following_controller_config_t;

typedef struct {
    float           pTerm;
    float           dTerm;
    float           controlOutput;
    int16_t         error;
    int16_t         previousError;
    int16_t         leftMotorVelocity;
    int16_t         previousLeftMotorVelocity;
    int16_t         rightMotorVelocity;
    int16_t         previousRightMotorVelocity;
    uint16_t        moduloSpinOffsetCounter;
    unsigned long   lastSpinTime;
    unsigned long   lastSpinDuration;
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

robot_status_t lineFollowingController_startUp();

robot_status_t lineFollowingController_shutDown();

line_following_controller_config_t* lineFollowingController_getConfig();

line_following_controller_state_t* lineFollowingController_getState();

#endif // LINE_FOLLOWING_CONTROLLER