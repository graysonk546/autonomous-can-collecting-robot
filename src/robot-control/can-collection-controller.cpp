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
    .inwardsRollerSpeed = 255,
    .outwardsRollerSpeed = 200,
    .loaderServoIdleAngle = 0,
    .loaderServoDepositAngle = 150,
    .maxRollerStallDuration = 5000ul,
    .tolerableRollerStallDuration = 500ul,
    .canDetectionToInsertionDelay = 1000ul,
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
    attachInterrupt(digitalPinToInterrupt(PIN_CAN_DETECTOR), _canDetected_ISR, FALLING);

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
    else if (state.nextLoaderState == WAITING_TO_LOAD)
    {
        state.loaderState = WAITING_TO_LOAD;
        if (state.previousLoaderState == WAITING_FOR_CAN)
        {
            Serial.print("Can detected at ");
            Serial.println(timeNow);
            state.timeLastCanDetected = timeNow;
        }
        else if (timeNow - state.timeLastCanDetected > config.canDetectionToInsertionDelay)
        {
            Serial.print("WAITING_FOR_CAN --> LOADING_CAN at ");
            Serial.println(timeNow);
            state.loaderState = LOADING_CAN;
            state.timeLastLoadingStarted = timeNow;
        }
    }
    else if (state.nextLoaderState == LOADING_CAN)
    {
        if (timeNow - state.timeLastLoadingStarted > config.loaderServoRotationTimeout)
        {
            Serial.print("LOADING_CAN --> RESETTING_LOADER at ");
            Serial.println(timeNow);
            state.loaderState = RESETTING_LOADER;
            state.timeLastLoaderResettingStarted = timeNow;
        }
    }
    else if (state.nextLoaderState == RESETTING_LOADER)
    {
        if (timeNow - state.timeLastLoaderResettingStarted > config.loaderServoRotationTimeout)
        {
            Serial.print("RESETTING_CAN --> WAITING_FOR_CAN at ");
            Serial.println(timeNow);
            state.loaderState = WAITING_FOR_CAN;
        }
    }
    state.nextLoaderState = state.loaderState;

    if (state.loaderState == WAITING_FOR_CAN || state.loaderState == RESETTING_LOADER || state.loaderState == WAITING_TO_LOAD)
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
    if (state.loaderState == WAITING_FOR_CAN)
    {
        Serial.print("ISR switching from WAITING_FOR_CAN to WAITING_TO_LOAD at ");
        Serial.println(millis());
        state.nextLoaderState = WAITING_TO_LOAD;
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