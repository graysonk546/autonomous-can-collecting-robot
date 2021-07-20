
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
    int val = FLOAT_OFFSET * lineFollowingController_getConfig()->kp;

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKp(uint8_t argNumber, char* args[])
{

    lineFollowingController_getConfig()->kp = (float) atof((const char*) 
                                              args[0]);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKd(uint8_t argNumber, char* args[])
{
    int val = FLOAT_OFFSET * lineFollowingController_getConfig()->kd;

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKd(uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->kd = (float) atof((const char*)
                                              args[0]);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getKi(uint8_t argNumber, char* args[])
{
    int val = FLOAT_OFFSET * lineFollowingController_getConfig()->ki;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            val);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setKi(uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->ki = (float) atof((const char*)
                                              args[0]);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getErr(uint8_t argNumber, char* args[])
{
    int error = lineFollowingController_getState()->error;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            error);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setTarg(uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->targetVelocity = (uint8_t) strtol(
                                                          (const char*) args[0],
                                                          NULL, 0);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getTarg(uint8_t argNumber, char* args[])
{
    uint8_t targ = lineFollowingController_getConfig()->targetVelocity;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            targ);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setMax(uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->maxEffSpeed = (uint8_t) strtol((const
                                                       char*) args[0], NULL, 0);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getMax(uint8_t argNumber, char* args[])
{
    uint8_t max = lineFollowingController_getConfig()->maxEffSpeed;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            max);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setMin(uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->minEffSpeed = (uint8_t) strtol((const
                                                       char*) args[0], NULL, 0);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getMin(uint8_t argNumber, char* args[])
{
    uint8_t min = lineFollowingController_getConfig()->minEffSpeed;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            min);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getDelocalizedGain(uint8_t argNumber,
                                                            char* args[])
{
    float gain = lineFollowingController_getConfig()->delocalizedGain;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %f}" CMD_EOL_STR, 
            gain);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setDelocalizedGain(uint8_t argNumber,
                                                           char* args[])
{
    lineFollowingController_getConfig()->delocalizedGain = (float)
                                                           atof((const char*)
                                                           args[0]);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_getDelocalizedReflectanceThreshold(
    uint8_t argNumber, char* args[])
{
    uint16_t thresh = lineFollowingController_getConfig()->
                      delocalizedReflectanceThreshold;
    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            thresh);
    Serial.print(str);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_setDelocalizedReflectanceThreshold(
    uint8_t argNumber, char* args[])
{
    lineFollowingController_getConfig()->delocalizedReflectanceThreshold =
        (u_int16_t ) strtol((const char*) args[0], NULL, 0);
    Serial.print(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR);
    return COMMAND_OK;
}

cli_status_t cliLineFollowingController_poll(uint8_t argNumber, char* args[])
{
    line_following_controller_config_t config;
    config = *lineFollowingController_getConfig();

    line_following_controller_state_t state;
    state = *lineFollowingController_getState();

    char str[1000];
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": {\"controller\":"
            " {\"config\": {\"kp\": %f, \"ki\": %f, \"kd\": %f, "
            "\"delocalizedGain\": %f, \"minEffSpeed\": %i, "
            "\"maxEffSpeed\": %i, \"targetVelocity\": %i,"
            " \"maxITermMagnitude\": %i, "
            "\"delocalizedReflectanceThreshold\": %i}, \"state\": "
            "{\"pTerm\": %f, \"iTerm\": %f, \"dTerm\": %f, "
            "\"controlOutput\": %f, \"error\": %i, \"previousError\": %i, "
            "\"leftMotorVelocity\": %i, \"previousLeftMotorVelocity\": %i, "
            "\"rightMotorVelocity\": %i, \"previousRightMotorVelocity\": %i, "
            "\"initialized\": %i}}, \"reflectance\": {\"left\": "
            "{\"value\": %i}, \"right\":{\"value\": %i}}, \"motors\": "
            "{\"left\": {\"speed\": %i, \"direction\": %i}, \"right\": "
            "{\"speed\": %i, \"direction\": %i}}}}" CMD_EOL_STR,
            config.kp, config.ki, config.kd, config.delocalizedGain,
            config.minEffSpeed, config.maxEffSpeed, config.targetVelocity,
            config.maxITermMagnitude, config.delocalizedReflectanceThreshold,
            state.pTerm, state.iTerm, state.dTerm, state.controlOutput,
            state.error, state.previousError, state.leftMotorVelocity,
            state.previousLeftMotorVelocity, state.rightMotorVelocity,
            state.previousRightMotorVelocity, state.initialized,
            config.reflectanceArr[LEFT_REFLECTANCE]->value,
            config.reflectanceArr[RIGHT_REFLECTANCE]->value,
            config.motorArr[LEFT_DRIVING_MOTOR]->speed,
            config.motorArr[LEFT_DRIVING_MOTOR]->direction,
            config.motorArr[RIGHT_DRIVING_MOTOR]->speed,
            config.motorArr[RIGHT_DRIVING_MOTOR]->direction);
    Serial.print(str);
    return COMMAND_OK;
}