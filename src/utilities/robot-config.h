#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef enum {
    PIN_LEFT_DRIVING_MOTOR_CW          = PB7,
    PIN_LEFT_DRIVING_MOTOR_CCW         = PB6,
    PIN_RIGHT_DRIVING_MOTOR_CW         = PB8,
    PIN_RIGHT_DRIVING_MOTOR_CCW        = PB9,
    PIR_ROLLER_MOTOR                   = PA7,
    PIN_ROLLER_MOTOR_ENCODER           = PA15,
    PIN_RIGHT_LINE_FOLLOWING_IR_SENSOR = PA5,
    PIN_LEFT_LINE_FOLLOWING_IR_SENSOR  = PA4,
    PIN_ROLLER_CW                      = PB0,
    PIN_ROLLER_CCW                     = PB1,
    PIN_CAN_DETECTOR                   = PB3,
    PIN_HOPPER_ROTATION_SERVO          = PA0,
    PIN_HOPPER_LOADING_SERVO           = PA1,
    PIN_BUTTON                         = PB14,
    PIN_RETURN_VEHICLE_DETECTOR        = PB4
} robot_pin_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

#endif // ROBOT_CONFIG_H