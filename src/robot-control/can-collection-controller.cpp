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
    .maxRollerStallDuration = 5000ul,
    .tolerableRollerStallDuration = 500ul,
    // .canDetectedISR = &(_canDetected_ISR),
    .canDetectionToInsertionDelay = 2500ul
};

static can_collection_controller_state_t state =
{
    .rollerMotor = 0,
    .rollerEncoder = 0,
    .mode = ROLLING_INWARDS,
    .canLoadingInProgress = false,
    .timeLastCanDetected = 0,
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
                                            rollerEncoder)
{
    if (rollerMotor->id != ROLLER_DRIVING_MOTOR)
    {
        return ROBOT_ERR;
    }
    else if (rollerEncoder->id != ROLLER_SPEED_ENCODER)
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
    pinMode(PIN_CAN_DETECTOR, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_CAN_DETECTOR), _canDetected_ISR, RISING);

    state.rollerMotor = rollerMotor;
    state.rollerEncoder = rollerEncoder;
    state.mode = ROLLING_INWARDS;
    state.canLoadingInProgress = false;
    state.timeLastCanDetected = millis();
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

    if (state.canLoadingInProgress)
    {
        if (timeNow - state.timeLastCanDetected > config.canDetectionToInsertionDelay)
        {
            Serial.print("Slapping initiated at");
            Serial.println(millis());
        }
    }

    if (state.mode == NOT_ROLLING)
    {
        dcMotorTwo_run(state.rollerMotor, STATIC_SPEED, CW_DIRECTION);
        return ROBOT_OK;
    }
    
    if (timeNow - state.rollerEncoder->lastInterruptTime > config.maxRollerStallDuration)
    {
        state.mode = NOT_ROLLING;
    }
    else if (timeNow - state.rollerEncoder->lastInterruptTime > config.tolerableRollerStallDuration)
    {
        state.mode = ROLLING_OUTWARDS;
    }
    else
    {
        state.mode = ROLLING_INWARDS;

    }

    if (state.mode == ROLLING_INWARDS)
    {
        dcMotorTwo_run(state.rollerMotor, config.inwardsRollerSpeed, CW_DIRECTION);
    }
    else if (state.mode == ROLLING_OUTWARDS)
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
    state.canLoadingInProgress = true;
    state.timeLastCanDetected = millis();
    Serial.print("Can detected at ");
    Serial.println(state.timeLastCanDetected);
}


can_collection_controller_config_t* canCollectionController_getConfig()
{
    return &config;
}

can_collection_controller_state_t* canCollectionController_getState()
{
    return &state;
}