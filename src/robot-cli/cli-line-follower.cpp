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

cli_status_t cliLineFollower_setThreshold(uint8_t argNumber, char* args[])
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

    lineFollower->threshold = (uint16_t) strtol(
                                        (const char*) args[1], NULL, 0);  

    Serial.print(Serial.print(F(CMD_JSON "{\"status\": \"success\"}" 
                                CMD_EOL_STR)));
    
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