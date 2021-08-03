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
} can_collection_controller_mode_t;

typedef struct {
    uint8_t inwardsRollerSpeed;
    uint8_t outwardsRollerSpeed;
    unsigned long maxRollerStallDuration;
    unsigned long tolerableRollerStallDuration;
    // void (*canDetectedISR)(void);
    unsigned long canDetectionToInsertionDelay;
} can_collection_controller_config_t;

typedef struct {

    dc_motor_two_t* rollerMotor;
    rotary_speed_encoder_t* rollerEncoder;
    can_collection_controller_mode_t mode;
    bool canLoadingInProgress;
    unsigned long timeLastCanDetected;
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
                                            rollerEncoder);

robot_status_t canCollectionController_spinOnce();

void canCollectionController_detectionISR();

can_collection_controller_config_t* canCollectionController_getConfig();

can_collection_controller_state_t* canCollectionController_getState();

#endif // CAN_COLLECTION_CONTROLLER