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

static uint8_t MIN_EFF_SPEED = 30;
static uint8_t MAX_EFF_SPEED = 255;
static uint8_t TARGET_VELOCITY = 150;
static uint8_t MAX_I_TERM_MAGNITUDE = 75;

/*******************************************************************************
*                               Structures
*******************************************************************************/

static pid_constant_t pidParameters =
{
    .kp = 1.0f,
    .ki = 0.0f,
    .kd = 0.0f
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

static reflectance_t* reflectanceArr[NUM_LINE_FOLLOWING_SENSORS];
static dc_motor_two_t* motorArr[NUM_DRIVING_MOTORS];

static bool controllerInitialized = false;

static int16_t error = 0;  // error is < 0 for left-bias and > 0 for right-bias
static int16_t previousError = 0;

static float pTerm = 0.0f;
static float iTerm = 0.0f;
static float dTerm = 0.0f;
static float controlOutput = 0.0f;

static int16_t leftMotorVelocity = TARGET_VELOCITY;
static int16_t rightMotorVelocity = TARGET_VELOCITY;

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t lineFollowingController_init(reflectance_t* sensor1,
                                            reflectance_t* sensor2,
                                            dc_motor_two_t* motor1,
                                            dc_motor_two_t* motor2)
{
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
    if (!controllerInitialized)
    {
        return ROBOT_ERR;
    }

    previousError = error;
    error = reflectanceArr[LEFT_REFLECTANCE]->value -
            reflectanceArr[RIGHT_REFLECTANCE]->value;

    pTerm = pidParameters.kp * error;
    iTerm += pidParameters.ki * error;
    dTerm = pidParameters.kd * (error - previousError);
    iTerm = CLAMP(iTerm, -MAX_I_TERM_MAGNITUDE, MAX_I_TERM_MAGNITUDE);

    controlOutput = pTerm + iTerm + dTerm;

    if (controlOutput < 0)
    {
        leftMotorVelocity = TARGET_VELOCITY + controlOutput;
        rightMotorVelocity = TARGET_VELOCITY - controlOutput;
    }
    else if (controlOutput > 0)
    {
        leftMotorVelocity = TARGET_VELOCITY - controlOutput;
        rightMotorVelocity = TARGET_VELOCITY + controlOutput;
    }
    else
    {
        leftMotorVelocity = rightMotorVelocity = TARGET_VELOCITY;
    }

    if (leftMotorVelocity >= 0)
    {
        dcMotorTwo_run(motorArr[LEFT_DRIVING_MOTOR],
                       CLAMP(leftMotorVelocity, MIN_EFF_SPEED,
                       MAX_EFF_SPEED), CW_DIRECTION);
    }
    else
    {
        dcMotorTwo_run(motorArr[LEFT_DRIVING_MOTOR],
                       CLAMP(-leftMotorVelocity, MIN_EFF_SPEED,
                       MAX_EFF_SPEED), CCW_DIRECTION);
    }
    if (rightMotorVelocity >= 0)
    {
        dcMotorTwo_run(motorArr[RIGHT_DRIVING_MOTOR],
                       CLAMP(rightMotorVelocity, MIN_EFF_SPEED,
                       MAX_EFF_SPEED), CW_DIRECTION);
    }
    else
    {
        dcMotorTwo_run(motorArr[RIGHT_DRIVING_MOTOR],
                       CLAMP(-rightMotorVelocity, MIN_EFF_SPEED,
                       MAX_EFF_SPEED), CCW_DIRECTION);
    }
    return ROBOT_OK;
}

pid_constant_t* lineFollowingController_getPidConstants()
{
    return &pidParameters;
}

uint8_t* lineFollowingController_getMinEffSpeed()
{
    return &MIN_EFF_SPEED;
}

uint8_t* lineFollowingController_getMaxEffSpeed()
{
    return &MAX_EFF_SPEED;
}