/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "line-following-controller.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define MAX_I_TERM 50
#define MIN_EFF_MOTOR_SPEED 30
#define MAX_EFF_MOTOR_SPEED 250

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static line_follower_t* lineFollowerArr[NUM_LINE_FOLLOWING_SENSORS];
static dc_motor_two_t* motorArr[NUM_DRIVING_MOTORS];
static bool controllerInitialized = false;
static line_following_error_t error = NO_ERROR;
static line_following_error_t previousError = NO_ERROR;
static int gain = 1;
static int pTerm = 0;
static int iTerm = 0;
static int dTerm = 0;
static int pidTerm = 0;
static int kp = 0;
static int ki = 0;
static int kd = 0;
static int leftMotorSpeed = MIN_EFF_MOTOR_SPEED;
static int rightMotorSpeed = MIN_EFF_MOTOR_SPEED;

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t lineFollowingController_init(reflectance_t* sensor1,
                                            reflectance_t* sensor2,
                                            dc_motor_two_t* motor1,
                                            dc_motor_two_t* motor2)
{
    reflectance_t* reflectanceArr[NUM_LINE_FOLLOWING_SENSORS];
    if (sensor1->id == RIGHT_REFLECTANCE && sensor2->id == LEFT_REFLECTANCE)
    {
        reflectanceArr[RIGHT_REFLECTANCE] = sensor1;
        reflectanceArr[LEFT_REFLECTANCE] = sensor2;
    }
    else if (sensor1->id == LEFT_REFLECTANCE &&
             sensor2->id == RIGHT_REFLECTANCE)
    {
        reflectanceArr[LEFT_REFLECTANCE] = sensor1;
        reflectanceArr[RIGHT_REFLECTANCE] = sensor2;
    }
    else
    {
        return ROBOT_ERR;
    }

    if (motor1->id == RIGHT_DRIVING_MOTOR && motor2->id == LEFT_DRIVING_MOTOR)
    {
        motorArr[RIGHT_DRIVING_MOTOR] = motor1;
        motorArr[LEFT_DRIVING_MOTOR] = motor2;
    }
    else if (motor1->id == LEFT_DRIVING_MOTOR &&
             motor2->id == RIGHT_DRIVING_MOTOR)
    {
        motorArr[LEFT_DRIVING_MOTOR] = motor1;
        motorArr[RIGHT_DRIVING_MOTOR] = motor2;
    }
    else
    {
        return ROBOT_ERR;
    }

    for (uint8_t i = 0; i < NUM_LINE_FOLLOWING_SENSORS; i++)
    {
        if (!reflectanceArr[i]->initialized &&
            reflectance_init(reflectanceArr[i]) == ROBOT_ERR)
        {
            return ROBOT_ERR;
        }
        lineFollowerArr[i] = lineFollower_get((line_follower_id_t) i);
        if (!lineFollowerArr[i]->initialized &&
            lineFollower_init(lineFollowerArr[i], reflectanceArr[i]) ==
            ROBOT_ERR)
        {
            return ROBOT_ERR;
        }
    }

    for (uint8_t j = 0; j < NUM_DRIVING_MOTORS; j++)
    {
        if (!motorArr[j]->initialized &&
            dcMotorTwo_init(motorArr[j]) == ROBOT_ERR)
        {
            return ROBOT_ERR;
        }
    }
    controllerInitialized = true;
    return ROBOT_OK;
}

robot_status_t lineFollowingController_spinOnce()
{
    if (!controllerInitialized) return ROBOT_ERR;

    for (uint8_t i = 0; i < NUM_LINE_FOLLOWING_SENSORS; i++)
    {
        lineFollower_update(lineFollowerArr[i]);
    }

    if (lineFollowerArr[LEFT_LINE_FOLLOWER]->status == ON_TAPE)
    {
        if (lineFollowerArr[RIGHT_LINE_FOLLOWER]->status == ON_TAPE)
        {
            error = NO_ERROR;
        }
        else
        {
            error = SLIGHT_RIGHT;
        }
    }
    else
    {
        if (lineFollowerArr[RIGHT_LINE_FOLLOWER]->status == ON_TAPE)
        {
            error = SLIGHT_LEFT;
        }
        else if (lineFollowerArr[RIGHT_LINE_FOLLOWER]->previousStatus ==
                 ON_TAPE)
        {
            error = FAR_RIGHT;
        }
        else if (lineFollowerArr[LEFT_LINE_FOLLOWER]->previousStatus ==
                 ON_TAPE)
        {
            error = FAR_LEFT;
        }
        else
        {
            return ROBOT_ERR;
        }
    }

    pTerm = kp * error;
    iTerm += ki * error;
    dTerm = kd * (error - previousError);
    iTerm = CLAMP(iTerm, -MAX_I_TERM, MAX_I_TERM);

    pidTerm = pTerm + dTerm + iTerm;

    if (pidTerm > 0)  // net error is to the right; need to turn left
    {
        leftMotorSpeed = MAX_EFF_MOTOR_SPEED - (gain * pidTerm);
        leftMotorSpeed = CLAMP(leftMotorSpeed, MIN_EFF_MOTOR_SPEED,
                               MAX_EFF_MOTOR_SPEED);
        rightMotorSpeed = MAX_EFF_MOTOR_SPEED;
    }
    else if (pidTerm < 0)  // net error is to the left; need to turn right
    {
        rightMotorSpeed = MAX_EFF_MOTOR_SPEED + (gain * pidTerm);
        rightMotorSpeed = CLAMP(rightMotorSpeed, MIN_EFF_MOTOR_SPEED,
                                MAX_EFF_MOTOR_SPEED);
        leftMotorSpeed = MAX_EFF_MOTOR_SPEED;
    }
    else  // no net error; go straight 
    {
        leftMotorSpeed = rightMotorSpeed = MAX_EFF_MOTOR_SPEED;
    }
    dcMotorTwo_run(motorArr[LEFT_DRIVING_MOTOR], leftMotorSpeed, CW_DIRECTION);
    dcMotorTwo_run(motorArr[RIGHT_DRIVING_MOTOR], rightMotorSpeed, 
                   CW_DIRECTION);
    return ROBOT_OK;
}