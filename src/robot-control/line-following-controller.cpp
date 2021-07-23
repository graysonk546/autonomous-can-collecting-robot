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

static void _runMotor(dc_motor_two_t* motor, int16_t velocity,
                      int16_t previousVelocity);

/*******************************************************************************
*                               Constants
*******************************************************************************/


#define ERROR_WINDOW_SIZE 100

/*******************************************************************************
*                               Structures
*******************************************************************************/

static line_following_controller_config_t config =
{
    .kp                              = 1.0f,
    .kd                              = 0.0f,
    .minEffSpeed                     = 30,
    .maxEffSpeed                     = 0,
    .targetVelocity                  = 105,
    .delocalizedReflectanceThreshold = 50,
    .previousSpinOffset              = 100,
    .delocalizedErrorMagnitude       = 200,
    .reflectanceArr                  = {0, 0},
    .motorArr                        = {0, 0}
};

static int16_t errorArr[ERROR_WINDOW_SIZE];
static int16_t errorIndex = 0;

static line_following_controller_state_t state =
{
    .pTerm                      = 0.0f,
    .dTerm                      = 0.0f,
    .controlOutput              = 0.0f,
    .error                      = 0,
    .previousError              = 0,
    .leftMotorVelocity          = config.targetVelocity,
    .previousLeftMotorVelocity  = 0,
    .rightMotorVelocity         = config.targetVelocity,
    .previousRightMotorVelocity = 0,
    .moduloSpinOffsetCounter    = 0,
    .lastSpinTime               = 0UL,
    .lastSpinDuration           = 0UL,
    .initialized                = false
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

    unsigned long timeNow = millis();
    state.lastSpinDuration = timeNow - state.lastSpinTime;
    state.lastSpinTime = timeNow;

    state.previousLeftMotorVelocity = state.leftMotorVelocity;
    state.previousRightMotorVelocity = state.rightMotorVelocity;

    reflectance_read(config.reflectanceArr[0]);
    reflectance_read(config.reflectanceArr[1]);

    if (config.reflectanceArr[LEFT_REFLECTANCE]->value <
        config.delocalizedReflectanceThreshold &&
        config.reflectanceArr[RIGHT_REFLECTANCE]->value <
        config.delocalizedReflectanceThreshold)
    {
        if (errorArr[errorIndex-1] > 0)
        {
            state.error = config.delocalizedErrorMagnitude;
        }
        else if (errorArr[errorIndex-1] < 0)
        {
            state.error = -config.delocalizedErrorMagnitude;
        }
        else
        {
           Serial.println("Catastrophic Error: delocalized previousError = 0");
        }
    }
    else
    {
        state.error = config.reflectanceArr[LEFT_REFLECTANCE]->value -
                      config.reflectanceArr[RIGHT_REFLECTANCE]->value;
    }

    state.pTerm = config.kp * state.error;

    if (errorIndex < ERROR_WINDOW_SIZE)
    {
        errorArr[errorIndex] = state.error;
        errorIndex++;
    }
    else
    {
        for (uint16_t i = 0; i < (ERROR_WINDOW_SIZE-1); i++)
        {
            errorArr[i] = errorArr[i+1];
        }
        errorArr[ERROR_WINDOW_SIZE-1] = state.error;
    }
    state.previousError = errorArr[0];
    state.dTerm = config.kd * (state.error - state.previousError);

    state.controlOutput = state.pTerm + state.dTerm;

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

    _runMotor(config.motorArr[LEFT_DRIVING_MOTOR], state.leftMotorVelocity,
              state.previousLeftMotorVelocity);
    
    _runMotor(config.motorArr[RIGHT_DRIVING_MOTOR], state.rightMotorVelocity,
              state.previousRightMotorVelocity);

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

static void _runMotor(dc_motor_two_t* motor, int16_t velocity,
                      int16_t previousVelocity)
{
    uint8_t speed;
    rotation_dir_t dir;
    if (velocity > config.maxEffSpeed)
    {
        speed = config.maxEffSpeed;
        dir = CW_DIRECTION;
    }
    else if (velocity > config.minEffSpeed)
    {
        speed = (uint8_t) velocity;
        dir = CW_DIRECTION;
    }
    else if (velocity > -config.minEffSpeed)
    {
        if (velocity > previousVelocity)
        {
            speed = config.minEffSpeed;
            dir = CW_DIRECTION;
        }
        else if (velocity < previousVelocity)
        {
            speed = config.minEffSpeed;
            dir = CCW_DIRECTION;
        }
        else
        {
            speed = motor->speed;
            dir = motor->direction;
        }
    }
    else if (velocity > -config.maxEffSpeed)
    {
        speed = (uint8_t) (-velocity);
        dir = CCW_DIRECTION;
    }
    else
    {
        speed = config.maxEffSpeed;
        dir = CCW_DIRECTION;
    }
    dcMotorTwo_run(motor, speed, dir);
}