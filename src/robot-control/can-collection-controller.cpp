/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "can-collection-controller.h"
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

static can_collection_controller_config_t config =
{
    .rollerSpeed = 200
};

static can_collection_controller_state_t state =
{
    .rollerMotor = 0,
    .initialized = false
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t canCollectionController_init(dc_motor_one_t* rollerMotor)
{
    if (!rollerMotor->id == ROLLER_MOTOR)
    {
        return ROBOT_ERR;
    }
    state.rollerMotor = rollerMotor;
    state.initialized = true;
    return ROBOT_OK;
}

robot_status_t canCollectionController_spinOnce()
{
    if (!state.initialized)
    {
        return ROBOT_ERR;
    }
    dcMotorOne_run(state.rollerMotor, config.rollerSpeed);
    return ROBOT_OK;
}

can_collection_controller_config_t* canCollectionController_getConfig()
{
    return &config;
}

can_collection_controller_state_t* canCollectionController_getState()
{
    return &state;
}