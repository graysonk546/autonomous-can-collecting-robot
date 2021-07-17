/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "line-following-controller.h"
#include "Arduino.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

static line_following_controller_config_t config =
{
    .kp                = 1.0f,
    .ki                = 0.0f,
    .kd                = 0.0f,
    .minEffSpeed       = 30,
    .maxEffSpeed       = 180,
    .targetVelocity    = 105,
    .maxITermMagnitude = 75,
    .reflectanceArr    = 0,
    .motorArr          = 0
};

static line_following_controller_state_t state =
{
    .pTerm              = 0.0f,
    .iTerm              = 0.0f,
    .dTerm              = 0.0f,
    .controlOutput      = 0.0f,
    .error              = 0,
    .previousError      = 0,
    .leftMotorVelocity  = config.targetVelocity,
    .rightMotorVelocity = config.targetVelocity,
    .initialized        = false
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

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
        config.reflectanceArr[RIGHT_REFLECTANCE] = sensor1;
        config.reflectanceArr[LEFT_REFLECTANCE] = sensor2;
    }
    else if (sensor1->id == LEFT_REFLECTANCE &&
             sensor2->id == RIGHT_REFLECTANCE)
    {
        config.reflectanceArr[LEFT_REFLECTANCE] = sensor1;
        config.reflectanceArr[RIGHT_REFLECTANCE] = sensor2;
    }
    else
    {
        return ROBOT_ERR;
    }

    if (motor1->id == RIGHT_DRIVING_MOTOR && motor2->id == LEFT_DRIVING_MOTOR)
    {
        config.motorArr[RIGHT_DRIVING_MOTOR] = motor1;
        config.motorArr[LEFT_DRIVING_MOTOR] = motor2;
    }
    else if (motor1->id == LEFT_DRIVING_MOTOR &&
             motor2->id == RIGHT_DRIVING_MOTOR)
    {
        config.motorArr[LEFT_DRIVING_MOTOR] = motor1;
        config.motorArr[RIGHT_DRIVING_MOTOR] = motor2;
    }
    else
    {
        return ROBOT_ERR;
    }

    for (uint8_t i = 0; i < NUM_LINE_FOLLOWING_SENSORS; i++)
    {
        if (!config.reflectanceArr[i]->initialized &&
            reflectance_init(config.reflectanceArr[i]) == ROBOT_ERR)
        {
            return ROBOT_ERR;
        }
    }

    for (uint8_t j = 0; j < NUM_DRIVING_MOTORS; j++)
    {
        if (!config.motorArr[j]->initialized &&
            dcMotorTwo_init(config.motorArr[j]) == ROBOT_ERR)
        {
            return ROBOT_ERR;
        }
    }
    state.initialized = true;
    return ROBOT_OK;
}

robot_status_t lineFollowingController_spinOnce()
{
    if (!state.initialized)
    {
        return ROBOT_ERR;
    }

    reflectance_read(config.reflectanceArr[0]);
    reflectance_read(config.reflectanceArr[1]);

    state.previousError = state.error;

    error = config.reflectanceArr[LEFT_REFLECTANCE]->value -
            config.reflectanceArr[RIGHT_REFLECTANCE]->value;

    pTerm = config.kp * state.error;
    iTerm += config.ki * state.error;
    dTerm = config.kd * (state.error - state.previousError);
    iTerm = CLAMP(state.iTerm, -config.maxITermMagnitude,
                  config.maxITermMagnitude);

    state.controlOutput = state.pTerm + state.iTerm + state.dTerm;

    if (state.controlOutput < 0)
    {
        state.leftMotorVelocity = config.targetVelocity - state.controlOutput;
        state.rightMotorVelocity = config.targetVelocity + state.controlOutput;
    }
    else if (state.controlOutput > 0)
    {
        state.leftMotorVelocity = config.targetVelocity - state.controlOutput;
        state.rightMotorVelocity = config.targetVelocity + state.controlOutput;
    }
    else
    {
        state.leftMotorVelocity = config.targetVelocity;
        state.rightMotorVelocity = config.targetVelocity;
    }

    if (state.leftMotorVelocity >= 0)
    {
        dcMotorTwo_run(config.motorArr[LEFT_DRIVING_MOTOR],
                       CLAMP(state.leftMotorVelocity, config.minEffSpeed,
                       config.maxEffSpeed), CW_DIRECTION);
    }
    else
    {
        dcMotorTwo_run(config.motorArr[LEFT_DRIVING_MOTOR],
                       CLAMP(-state.leftMotorVelocity, config.minEffSpeed,
                       config.maxEffSpeed), CCW_DIRECTION);
    }
    if (state.rightMotorVelocity >= 0)
    {
        dcMotorTwo_run(config.motorArr[RIGHT_DRIVING_MOTOR],
                       CLAMP(state.rightMotorVelocity, config.minEffSpeed,
                       config.maxEffSpeed), CW_DIRECTION);
    }
    else
    {
        dcMotorTwo_run(config.motorArr[RIGHT_DRIVING_MOTOR],
                       CLAMP(-state.rightMotorVelocity, config.minEffSpeed,
                       config.maxEffSpeed), CCW_DIRECTION);
    }
    return ROBOT_OK;
}

line_following_controller_config_t* lineFollowingController_getConfig()
{
    return &config;
}

line_following_controller_state_t* lineFollowingController_getState()
{
    return &state;
}