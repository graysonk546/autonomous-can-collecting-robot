
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-line-following-controller.h"
#include "stdio.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define FLOAT_OFFSET 1000.0F

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
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    int val = FLOAT_OFFSET * pidConstants->kp;

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKp(uint8_t argNumber, char* args[])
{
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    pidConstants->kp = (float) atof((const char*) args[0]);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKd(uint8_t argNumber, char* args[])
{
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    int val = FLOAT_OFFSET * pidConstants->kd;

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKd(uint8_t argNumber, char* args[])
{
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    pidConstants->kd = (float) atof((const char*) args[0]);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKi(uint8_t argNumber, char* args[])
{
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    int val = FLOAT_OFFSET * pidConstants->ki;

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKi(uint8_t argNumber, char* args[])
{
    pid_constant_t* pidConstants = 
                    lineFollowingController_getPidConstants();

    pidConstants->ki = (float) atof((const char*) args[0]);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getErr(uint8_t argNumber, char* args[])
{
    int error = *lineFollowingController_getError();
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            error);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setTarg(uint8_t argNumber, char* args[])
{
    uint8_t targ = lineFollowingController_getTargSpeed();
    
    targ = (uint8_t) strtol((const char*) args[0], NULL, 0);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getTarg(uint8_t argNumber, char* args[])
{
    uint8_t targ = *lineFollowingController_getTargSpeed();
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            targ);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setMax(uint8_t argNumber, char* args[])
{
    uint8_t max = lineFollowingController_getMaxEffSpeed();
    
    max = (uint8_t) strtol((const char*) args[0], NULL, 0);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getMax(uint8_t argNumber, char* args[])
{
    uint8_t max = *lineFollowingController_getMaxEffSpeed();
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            max);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setMin(uint8_t argNumber, char* args[])
{
    uint8_t min = lineFollowingController_getMinEffSpeed();
    
    min = (uint8_t) strtol((const char*) args[0], NULL, 0);

    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getMin(uint8_t argNumber, char* args[])
{
    uint8_t min = *lineFollowingController_getMinEffSpeed();
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            min);
    Serial.print(str);
    return COMMAND_OK;
}