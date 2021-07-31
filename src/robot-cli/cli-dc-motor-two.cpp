
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-dc-motor-two.h"
#include "robot-core/dc-motor-two.h"
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

cli_status_t cliDcMotorTwo_init(uint8_t argNumber, char* args[])
{
    dc_motor_two_id_t motor_id = (dc_motor_two_id_t) strtol((const char*)
                                                            args[0], NULL, 0);
    dc_motor_two_t* motor;
    if (motor_id == LEFT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(LEFT_DRIVING_MOTOR);
    }
    else if (motor_id == RIGHT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(RIGHT_DRIVING_MOTOR);
    }
    else if (motor_id == ROLLER_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(ROLLER_DRIVING_MOTOR);
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    if (dcMotorTwo_init(motor) == ROBOT_OK)
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

cli_status_t cliDcMotorTwo_run(uint8_t argNumber, char* args[])
{
    dc_motor_two_id_t motor_id = (dc_motor_two_id_t) strtol((const char*)
                                                            args[0], NULL, 0);
    uint8_t speed = (uint8_t) strtol((const char*) args[1], NULL, 0);

    dc_motor_two_t* motor;
    if (motor_id == LEFT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(LEFT_DRIVING_MOTOR);
    }
    else if (motor_id == RIGHT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(RIGHT_DRIVING_MOTOR);
    }
    else if (motor_id == ROLLER_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(ROLLER_DRIVING_MOTOR);
    }
    else
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

    rotation_dir_t direction;
    if (strcmp(args[2], "cw") == 0)
    {
        direction = CW_DIRECTION;
    }
    else if (strcmp(args[2], "ccw") == 0)
    {
        direction = CCW_DIRECTION;
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " direction\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    if (dcMotorTwo_run(motor, speed, direction) == ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
    }
    else
    {
         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"motor run"
                     " failed\"}" CMD_EOL_STR));
    }

    return COMMAND_OK;
}

cli_status_t cliDcMotorTwo_getSpeed(uint8_t argNumber, char* args[])
{
    dc_motor_two_id_t motor_id = (dc_motor_two_id_t) strtol((const char*)
                                                            args[0], NULL, 0);

    dc_motor_two_t* motor;
    if (motor_id == LEFT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(LEFT_DRIVING_MOTOR);
    }
    else if (motor_id == RIGHT_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(RIGHT_DRIVING_MOTOR);
    }
    else if (motor_id == ROLLER_DRIVING_MOTOR)
    {
        motor = dcMotorTwo_get(ROLLER_DRIVING_MOTOR);
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }

    char str[100]; 
    sprintf(str, CMD_JSON "{\"status\": \"success\", \"data\": %i}" CMD_EOL_STR, 
            (int) motor->speed);
    Serial.print(str);
    return COMMAND_OK;
}
