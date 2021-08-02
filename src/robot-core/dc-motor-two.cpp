
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "dc-motor-two.h"
#include "utilities/robot-config.h"

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

static dc_motor_two_t dcMotorTwoArr[] =
{
    [RIGHT_DRIVING_MOTOR] =
    {
        .cw_pin      = PIN_RIGHT_DRIVING_MOTOR_CW,
        .ccw_pin     = PIN_RIGHT_DRIVING_MOTOR_CCW,
        .direction   = CW_DIRECTION,
        .speed       = STATIC_SPEED,
        .id          = RIGHT_DRIVING_MOTOR,
        .initialized = false
    },
    [LEFT_DRIVING_MOTOR] =
    {
        .cw_pin      = PIN_LEFT_DRIVING_MOTOR_CW,
        .ccw_pin     = PIN_LEFT_DRIVING_MOTOR_CCW,
        .direction   = CW_DIRECTION,
        .speed       = STATIC_SPEED,
        .id          = LEFT_DRIVING_MOTOR,
        .initialized = false
    },
    [ROLLER_DRIVING_MOTOR] = 
    {
        .cw_pin      = PIN_ROLLER_CW,
        .ccw_pin     = PIN_ROLLER_CCW,
        .direction   = CW_DIRECTION,
        .speed       = STATIC_SPEED,
        .id          = ROLLER_DRIVING_MOTOR,
        .initialized = false
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t dcMotorTwo_init(dc_motor_two_t* motor)
{
    pinMode(motor->cw_pin, OUTPUT);
    pinMode(motor->ccw_pin, OUTPUT);
    motor->speed = STATIC_SPEED;
    analogWrite(motor->cw_pin, motor->speed);
    analogWrite(motor->ccw_pin, motor->speed);
    motor->initialized = true;
    return ROBOT_OK;
}

robot_status_t dcMotorTwo_run(dc_motor_two_t* motor, uint8_t speed,
                              rotation_dir_t direction)
{
    if (motor->initialized)
    {
        motor->speed = speed;
        motor->direction = direction;
        if (direction == CW_DIRECTION) 
        {
            analogWrite(motor->cw_pin, motor->speed);
            analogWrite(motor->ccw_pin, STATIC_SPEED);
        }
        else
        {
            analogWrite(motor->cw_pin, STATIC_SPEED);
            analogWrite(motor->ccw_pin, motor->speed);
        }
        return ROBOT_OK;
    }
    else
    {
        return ROBOT_ERR;
    }
}

dc_motor_two_t* dcMotorTwo_get(dc_motor_two_id_t id)
{
    return &dcMotorTwoArr[id];
}