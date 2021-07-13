
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

// static void _runMotorFeedback(dc_motor_t motor, uint8_t speed, 
//                               dc_motor_dir_t dir);

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
    // parse motor id from cli entry
    motor_id_t motor_id = (motor_id_t) strtol((const char*) args[0], NULL, 0);

    if (motor_id != MOTOR_3)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                     " motor\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    // get pointer to dc motor type corresponding to id
    dc_motor_one_t* motor = dcMotorOne_get(motor_id);
    // initilize the motor

    // elicite response message in json format to the serial terminal
    if (dcMotorOne_init(motor) != ROBOT_OK)
    {
        Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"motor init"
                     " failed\"}" CMD_EOL_STR));        
    }
    else
    {
        Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
    }
    return COMMAND_OK;
}

cli_status_t cliDcMotorOne_run(uint8_t argNumber, char* args[])
{
    motor_id_t motor_id = (motor_id_t) strtol((const char*) args[0], NULL, 0);
    uint8_t speed = (uint8_t) strtol((const char*) args[1], NULL, 0);

    if (motor_id != MOTOR_3)
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

// cli_status_t cliDcMotor_run(uint8_t argNumber, char* args[])
// {
//     motor_id_t motor_id = (motor_id_t) strtol((const char*) args[0], 
//                                            NULL, 0);
//     uint8_t speed = (uint8_t) strtol((const char*) args[1], 
//                                      NULL, 0);
//     if (motor != MOTOR_3)
//     {
//         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
//                      " motor\"}" CMD_EOL_STR));
//         return COMMAND_OK;
//     }
//     if (speed < STATIC_SPEED || speed > MAX_SPEED)
//     {
//         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": invalid"
//                      " speed\"}" CMD_EOL_STR));
//         return COMMAND_OK;
//     }

//     if (strcmp(args[2], "left") == 0)
//     {
//         _runMotorFeedback(motor, speed, CC_DIRECTION);
//     }
//     else if (strcmp(args[2], "right") == 0)
//     {
//         _runMotorFeedback(motor, speed, CW_DIRECTION);
//     }
//     else
//     {
//         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
//                      " direction\"}" CMD_EOL_STR));
//     }
//     return COMMAND_OK;
// }

// static void _runMotorFeedback(dc_motor_t motor, uint8_t speed, 
//                                         dc_motor_dir_t dir)
// {
//     if (dcMotor_run(motor, speed, dir) != ROBOT_OK)
//     {
//         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"motor run"
//                      " failed\"}" CMD_EOL_STR));
//     }
//     Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
// }
