/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-servo.h"
#include "robot-core/servo.h"
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

cli_status_t cliServo_init(uint8_t argNumber, char* args[])
{
    servo_id_t servo_id = (servo_id_t) strtol((const char*) args[0], NULL, 0);

    if (servo_id != HOPPER_ROTATION_SERVO)
    {
         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " reflectance sensor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    servo_t* servo = servo_get(servo_id);

    if (servo_init(servo) == ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));   
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"servo init"
                     " failed\"}" CMD_EOL_STR));
    }
    return COMMAND_OK;
}

cli_status_t cliServo_rotate(uint8_t argNumber, char* args[])
{
    servo_id_t servo_id = (servo_id_t) strtol((const char*) args[0], NULL, 0);
    uint8_t angle = (uint8_t) strtol((const char*) args[1], NULL, 0);
    if (servo_id != HOPPER_ROTATION_SERVO)
    {
         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                      " reflectance sensor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    servo_t* servo = servo_get(servo_id);

    if (angle > MAX_ANGLE || angle < MIN_ANGLE)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": invalid"
                     " angle\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    if (servo_rotate(servo, angle) == ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
    }
    else
    {
         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": "
                      "\"servo rotate failed\"}" CMD_EOL_STR));
    }
    return COMMAND_OK;
}
