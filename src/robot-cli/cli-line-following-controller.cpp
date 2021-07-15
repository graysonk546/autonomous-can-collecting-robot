
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "utilities/util-vars.h"
#include "cli-line-following-controller.h"

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

cli_status_t cliLineFollowingController_getKp(uint8_t argNumber, char* args[])
{
    pid_constant_t* lineFollowingController_getPidConstants();
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKp(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKd(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKd(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKi(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKi(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getGain(uint8_t argNumber, 
                                                char* args[])
{
    return COMMAND_OK;                          
}

cli_status_t cliLineFollowingController_setGain(uint8_t argNumber, 
                                                char* args[])
{
    return COMMAND_OK;
}