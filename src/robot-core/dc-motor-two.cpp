
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "dc-motor-two.h"

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

robot_status_t dcMotorTwo_init(dc_motor_two_t* motor, uint8_t cw_pin_number,
                              uint8_t ccw_pin_number)
{
    motor->cw_pin = cw_pin_number;
    motor->ccw_pin = ccw_pin_number;
    motor->direction = CW_DIRECTION;
    motor->speed = STATIC_SPEED;

    pinMode(motor->cw_pin, OUTPUT);
    pinMode(motor->ccw_pin, OUTPUT);
    analogWrite(motor->cw_pin, motor->speed);
    analogWrite(motor->ccw_pin, motor->speed);

    return ROBOT_OK;
}

robot_status_t dcMotorTwo_run(dc_motor_two_t* motor, uint8_t speed,
                             rotation_dir_t direction)
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