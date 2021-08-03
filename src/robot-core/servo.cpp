/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "servo.h"
#include "utilities/robot-config.h"
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

static servo_motor_t servoArr[] =
{
    [HOPPER_ROTATION_SERVO] =
    {
        .pin = PIN_HOPPER_ROTATION_SERVO,
        .angle = 0,
        .id = HOPPER_ROTATION_SERVO,
        .initialized = false,
        .initAngle = 0

    },
    [HOPPER_LOADING_SERVO] = 
    {
        .pin = PIN_HOPPER_LOADING_SERVO,
        .angle = 0,
        .id = HOPPER_LOADING_SERVO,
        .initialized = false,
        .initAngle = 0
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t servo_init(servo_motor_t* servo)
{
    servo->motor.attach(servo->pin);
    servo->motor.write(servo->initAngle);
    servo->initialized = true;
    return ROBOT_OK;
}

robot_status_t servo_rotate(servo_motor_t* servo, uint8_t angle)
{
    if (servo->initialized)
    {
        servo->angle = CLAMP(angle, MIN_ANGLE, MAX_ANGLE);
        Serial.println("Calling servo write...");
        servo->motor.write(servo->angle);
        return ROBOT_OK;
    }
    else
    {
        return ROBOT_ERR;
    }
}

servo_motor_t* servo_get(servo_motor_id_t id)
{
    return &servoArr[id];
}