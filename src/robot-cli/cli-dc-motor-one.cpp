
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-dc-motor-one.h"
#include "robot-core/dc-motor-one.h"
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

cli_status_t cliDcMotorOne_init(uint8_t argNumber, char* args[])
{
    dc_motor_one_id_t motor_id = (dc_motor_one_id_t) strtol((const char*)
                                                            args[0], NULL, 0);
    if (motor_id != ROLLER_MOTOR)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    dc_motor_one_t* motor = dcMotorOne_get(motor_id);
    if (dcMotorOne_init(motor) == ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));   
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"motor init"
                     " failed\"}" CMD_EOL_STR));
    }
    return COMMAND_OK;
}

cli_status_t cliDcMotorOne_run(uint8_t argNumber, char* args[])
{
    dc_motor_one_id_t motor_id = (dc_motor_one_id_t) strtol((const char*)
                                                            args[0], NULL, 0);
    uint8_t speed = (uint8_t) strtol((const char*) args[1], NULL, 0);
    if (motor_id != ROLLER_MOTOR)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    if (speed > MAX_SPEED || speed < STATIC_SPEED)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": invalid"
                     " speed\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    dc_motor_one_t* motor = dcMotorOne_get(motor_id);
    if (dcMotorOne_run(motor, speed))
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
    }
    return COMMAND_OK;
}
