
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "dc-motor-one.h"

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

static dc_motor_one_t dcMotorOneArr[] =
{
    [ROLLER_MOTOR] = 
    {
        .pin         = PA7,
        .speed       = STATIC_SPEED,
        .id          = ROLLER_MOTOR,
        .initialized = false
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t dcMotorOne_init(dc_motor_one_t* motor)
{
    pinMode(motor->pin, OUTPUT);
    motor->speed = STATIC_SPEED;
    analogWrite(motor->pin, motor->speed);
    motor->initialized = true;
    return ROBOT_OK;
}

robot_status_t dcMotorOne_run(dc_motor_one_t* motor, uint8_t speed)
{
    if (motor->initialized)
    {
        motor->speed = speed;
        analogWrite(motor->pin, motor->speed);
        return ROBOT_OK;
    }
    else
    {
        return ROBOT_ERR;
    }
}

dc_motor_one_t* dcMotorOne_get(dc_motor_one_id_t id) 
{
    return &dcMotorOneArr[id];
}