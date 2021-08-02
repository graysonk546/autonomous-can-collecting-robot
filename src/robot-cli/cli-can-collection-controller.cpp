/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-can-collection-controller.h"
#include "stdio.h"

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
                                                       char* args[])
{
    int8_t speed = canCollectionController_getConfig()->rollerSpeed;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            speed);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliCanCollectionController_setRollerSpeed(uint8_t argNumber,
                                                       char* args[])
{
    canCollectionController_getConfig()->rollerSpeed = (uint8_t) strtol((const
                                                       char*) args[0], NULL, 0);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}