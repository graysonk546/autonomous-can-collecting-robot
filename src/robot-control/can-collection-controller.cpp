/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include "Arduino.h"

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "can-collection-controller.h"
#include "robot-core/rotary-speed-encoder.h"
#include "utilities/robot-config.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

static void _canDetected_ISR();

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

static can_collection_controller_config_t config =
{
    .inwardsRollerSpeed = 230,
    .outwardsRollerSpeed = 200,
    .loaderServoIdleAngle = 90,
    .loaderServoDepositAngle = 180,
    .maxRollerStallDuration = 5000ul,
    .tolerableRollerStallDuration = 500ul,
    .canDetectionToInsertionDelay = 2500ul,
    .loaderServoRotationTimeout = 500ul
};

static can_collection_controller_state_t state =
{
    .rollerMotor = 0,
    .rollerEncoder = 0,
    .rollerState = ROLLING_INWARDS,
    .loaderState = WAITING_FOR_CAN,
    .previousLoaderState = WAITING_FOR_CAN,
    .nextLoaderState = WAITING_FOR_CAN,
    .timeLastCanDetected = 0,
    .timeLastLoadingStarted = 0,
    .timeLastLoaderResettingStarted = 0,
    .initialized = false
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t canCollectionController_init(dc_motor_two_t* rollerMotor,
                                            rotary_speed_encoder_t*
                                            rollerEncoder,
                                            servo_motor_t* loaderServo)
{
    if (rollerMotor->id != ROLLER_DRIVING_MOTOR)
    {
        return ROBOT_ERR;
    }
    else if (rollerEncoder->id != ROLLER_SPEED_ENCODER)
    {
        return ROBOT_ERR;
    }
    else if (loaderServo->id != HOPPER_LOADING_SERVO)
    {
        return ROBOT_ERR;
    }

    if (!rollerMotor->initialized && dcMotorTwo_init(rollerMotor) == ROBOT_ERR)
    {
        return ROBOT_ERR;
    }
    else if (!rollerEncoder->initialized &&
             rotarySpeedEncoder_init(rollerEncoder) == ROBOT_ERR)
    {
        return ROBOT_ERR;
    }
    else if (!loaderServo->initialized && servo_init(loaderServo) == ROBOT_ERR)
    {
        return ROBOT_ERR;
    }

    pinMode(PIN_CAN_DETECTOR, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_CAN_DETECTOR), _canDetected_ISR, RISING);

    state.rollerMotor = rollerMotor;
    state.rollerEncoder = rollerEncoder;
    state.loaderServo = loaderServo;
    state.rollerState = ROLLING_INWARDS;
    state.loaderState = state.previousLoaderState = state.nextLoaderState = WAITING_FOR_CAN;
    state.timeLastCanDetected = state.timeLastLoadingStarted =
        state.timeLastLoaderResettingStarted = millis();
    state.initialized = true;
    return ROBOT_OK;
}

robot_status_t canCollectionController_spinOnce()
{

    if (!state.initialized)
    {
        return ROBOT_ERR;
    }

    const unsigned long timeNow = millis();

    state.previousLoaderState = state.loaderState;
    if (state.nextLoaderState == WAITING_FOR_CAN)
    {
        state.loaderState = WAITING_FOR_CAN;
    }
    else if (state.nextLoaderState == LOADING_CAN)
    {
        state.loaderState = LOADING_CAN;
        if (state.previousLoaderState == WAITING_FOR_CAN)
        {
            state.timeLastLoadingStarted = timeNow;
        }
        if (timeNow - state.timeLastLoadingStarted > config.loaderServoRotationTimeout)
        {
            state.loaderState = RESETTING_LOADER;
        }
    }
    else
    {
        state.loaderState = RESETTING_LOADER;
        if (state.previousLoaderState == LOADING_CAN)
        {
            state.timeLastLoaderResettingStarted = timeNow;
        }
        if (timeNow - state.timeLastLoaderResettingStarted > config.loaderServoRotationTimeout)
        {
            state.loaderState = WAITING_FOR_CAN;
        }
    }
    state.nextLoaderState = state.loaderState;

    if (state.loaderState == WAITING_FOR_CAN || state.nextLoaderState == RESETTING_LOADER)
    {
        servo_rotate(state.loaderServo, config.loaderServoIdleAngle);
    }
    else
    {
        servo_rotate(state.loaderServo, config.loaderServoDepositAngle);
    }
    
    if (state.rollerState != NOT_ROLLING)
    {
        if (timeNow - state.rollerEncoder->lastInterruptTime > config.maxRollerStallDuration)
        {
            state.rollerState = NOT_ROLLING;
        }
        else if (timeNow - state.rollerEncoder->lastInterruptTime > config.tolerableRollerStallDuration)
        {
            state.rollerState = ROLLING_OUTWARDS;
        }
        else
        {
            state.rollerState = ROLLING_INWARDS;
        }
    }

    if (state.rollerState == ROLLING_INWARDS)
    {
        dcMotorTwo_run(state.rollerMotor, config.inwardsRollerSpeed, CW_DIRECTION);
    }
    else if (state.rollerState == ROLLING_OUTWARDS)
    {
        dcMotorTwo_run(state.rollerMotor, config.outwardsRollerSpeed, CCW_DIRECTION);
    }
    else
    {
        dcMotorTwo_run(state.rollerMotor, STATIC_SPEED, CW_DIRECTION);
    }
    return ROBOT_OK;
}

static void _canDetected_ISR()
{
    Serial.println("_canDetected_ISR() called");
    if (state.loaderState == WAITING_FOR_CAN)
    {
        state.nextLoaderState = LOADING_CAN;
    }
}

can_collection_controller_config_t* canCollectionController_getConfig()
{
    return &config;
}

can_collection_controller_state_t* canCollectionController_getState()
{
    return &state;
}