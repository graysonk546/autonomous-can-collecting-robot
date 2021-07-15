/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-reflectance.h"
#include "robot-core/reflectance.h"
#include "robot-core/command.h"
#include "utilities/util-vars.h"

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

cli_status_t cliReflectance_init(uint8_t argNumber, char* args[])
{
    reflectance_id_t sensorId = (reflectance_id_t) strtol((const char*) args[0], 
                                                          NULL, 0);
    
    if (sensorId > LEFT_REFLECTANCE || sensorId < RIGHT_REFLECTANCE)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " reflectance sensor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    reflectance_t* sensor = reflectance_get(sensorId);

    if (reflectance_init(sensor) != ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"sensor"
                     " initialization failed\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    Serial.print(F(CMD_JSON "{\"status\": \"succcess\"}" CMD_EOL_STR));
    return COMMAND_OK;
}

cli_status_t cliReflectance_read(uint8_t argNumber, char* args[])
{
    reflectance_id_t sensorId = (reflectance_id_t) strtol((const char*) args[0], 
                                                          NULL, 0);
    
    if (sensorId > LEFT_REFLECTANCE || sensorId < RIGHT_REFLECTANCE)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " reflectance sensor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    reflectance_t* sensor = reflectance_get(sensorId);

    if (!sensor->initialized)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"sensor"
                     " not initialized\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    if (reflectance_read(sensor) != ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"sensor"
                     " read was not successful\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            (int) sensor->value);
    Serial.print(str);
    return COMMAND_OK;
}