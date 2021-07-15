/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-line-follower.h"
#include "robot-core/command.h"

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

cli_status_t cliLineFollower_init(uint8_t argNumber, char* args[])
{
    line_follower_id_t lineFollowerId = (line_follower_id_t) strtol(
                                        (const char*) args[0], NULL, 0);
    if (lineFollowerId > LEFT_LINE_FOLLOWER || 
        lineFollowerId < RIGHT_LINE_FOLLOWER)
    {
        Serial.print(Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\":"
                                  " \"invalid line follower\"}" CMD_EOL_STR)));
        return COMMAND_OK;
    }

    reflectance_id_t reflectanceId = (reflectance_id_t) strtol(
                                        (const char*) args[1], NULL, 0);

    if (reflectanceId > LEFT_REFLECTANCE || reflectanceId < RIGHT_REFLECTANCE)
    {
        Serial.print(Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\":"
                                  " \"invalid sensor\"}" CMD_EOL_STR)));
        return COMMAND_OK;
    }

    line_follower_t* lineFollower = lineFollower_get(lineFollowerId);
    reflectance_t* reflectance = reflectance_get(reflectanceId);

    if (lineFollower_init(lineFollower, reflectance) != ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\":"
                                  " \"initialization unsuccessful\"}" 
                                  CMD_EOL_STR));
        return COMMAND_OK;
    }

    Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
    return COMMAND_OK;
}

cli_status_t cliLineFollower_setThreshold(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}

cli_status_t cliLineFollower_getThreshold(uint8_t argNumber, char* args[])
{
    line_follower_id_t lineFollowerId = (line_follower_id_t) strtol(
                                        (const char*) args[0], NULL, 0);

    if (lineFollowerId > LEFT_LINE_FOLLOWER ||
        lineFollowerId < RIGHT_LINE_FOLLOWER)
    {
        Serial.print(Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\":"
                                  " \"invalid line follower\"}" CMD_EOL_STR)));
        return COMMAND_OK;
    }

    line_follower_t* lineFollower = lineFollower_get(lineFollowerId);

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            (int) lineFollower->threshold);
    Serial.print(str);
    return COMMAND_OK;
}