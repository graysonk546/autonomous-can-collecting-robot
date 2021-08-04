#ifndef CAN_COLLECTION_CONTROLLER
#define CAN_COLLECTION_CONTROLLER

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <stdint.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "utilities/util-vars.h"
#include "robot-core/dc-motor-two.h"
#include "robot-core/rotary-speed-encoder.h"
#include "robot-core/servo.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef enum {
    ROLLING_INWARDS,
    ROLLING_OUTWARDS,
    NOT_ROLLING
} can_roller_state_t;

typedef enum {
    WAITING_FOR_CAN,
    WAITING_TO_LOAD,
    LOADING_CAN,
    RESETTING_LOADER,
} can_loader_state_t;

typedef struct {
    uint8_t inwardsRollerSpeed;
    uint8_t outwardsRollerSpeed;
    uint8_t loaderServoIdleAngle;
    uint8_t loaderServoDepositAngle;
    unsigned long maxRollerStallDuration;
    unsigned long tolerableRollerStallDuration;
    unsigned long canDetectionToInsertionDelay;
    unsigned long loaderServoRotationTimeout;
} can_collection_controller_config_t;

typedef struct {

    dc_motor_two_t* rollerMotor;
    rotary_speed_encoder_t* rollerEncoder;
    servo_motor_t* loaderServo;
    can_roller_state_t rollerState;
    can_loader_state_t loaderState;
    can_loader_state_t previousLoaderState;
    can_loader_state_t nextLoaderState;
    unsigned long timeLastCanDetected;
    unsigned long timeLastLoadingStarted;
    unsigned long timeLastLoaderResettingStarted;
    bool initialized;
} can_collection_controller_state_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t canCollectionController_init(dc_motor_two_t* rollerMotor,
                                            rotary_speed_encoder_t*
                                            rollerEncoder,
                                            servo_motor_t* loaderServo);

robot_status_t canCollectionController_spinOnce();

void canCollectionController_detectionISR();

can_collection_controller_config_t* canCollectionController_getConfig();

can_collection_controller_state_t* canCollectionController_getState();

#endif // CAN_COLLECTION_CONTROLLER