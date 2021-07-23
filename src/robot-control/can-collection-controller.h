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
#include "robot-core/dc-motor-one.h"

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
    uint8_t rollerSpeed;
} can_collection_controller_config_t;

typedef struct {

    dc_motor_one_t* rollerMotor;
    bool initialized;
} can_collection_controller_state_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t canCollectionController_init(dc_motor_one_t* rollerMotor);

robot_status_t canCollectionController_spinOnce();

can_collection_controller_config_t* canCollectionController_getConfig();

can_collection_controller_state_t* canCollectionController_getState();

#endif // CAN_COLLECTION_CONTROLLER