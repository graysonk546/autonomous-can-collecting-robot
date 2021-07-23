#ifndef CLI_CAN_COLLECTION_CONTROLLER
#define CLI_CAN_COLLECTION_CONTROLLER
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "robot-core/command.h"
#include "utilities/util-vars.h"
#include "robot-control/can-collection-controller.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

cli_status_t cliCanCollectionController_getRollerSpeed(uint8_t argNumber,
                                                       char* args[]);

cli_status_t cliCanCollectionController_setRollerSpeed(uint8_t argNumber,
                                                       char* args[]);

#define CAN_COLLECTION_CONTROLLER_COMMANDS                                                                                                    \
    {cliCanCollectionController_getRollerSpeed,  "get-roller-speed",        "",     "get roller speed",  0, 0}, \
    {cliCanCollectionController_setRollerSpeed,  "set-roller-speed",   "<speed>",  "set roller speed",   1, 1},

#endif // CLI_CAN_COLLECTION_CONTROLLER
