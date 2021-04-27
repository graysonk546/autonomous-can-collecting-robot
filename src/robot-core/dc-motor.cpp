
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "dc-motor.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

static void _runDir(uint8_t pin1, uint8_t pin2, dc_motor_dir_t dir, 
                    uint8_t speed);
static void _initMotor(uint8_t pin1, uint8_t pin2, uint8_t power);

/*******************************************************************************
*                               Constants
*******************************************************************************/

#ifdef UNO
#define PIN_1_MOTOR_1  9
#define PIN_2_MOTOR_1  10
#define PIN_1_MOTOR_2  3
#define PIN_2_MOTOR_2  5
#define POWER_MOTOR_1  7
#define POWER_MOTOR_2  8
#elif STM32
#define PIN_1_MOTOR_1  PB8
#define PIN_2_MOTOR_1  PB9
#define PIN_1_MOTOR_2  PB6
#define PIN_2_MOTOR_2  PB7
#define POWER_MOTOR_1  PA15
#define POWER_MOTOR_2  PA12
#else
#define PIN_1_MOTOR_1  PB8
#define PIN_2_MOTOR_1  PB9
#define PIN_1_MOTOR_2  PB6
#define PIN_2_MOTOR_2  PB7
#define POWER_MOTOR_1  PA15
#define POWER_MOTOR_2  PA12
#endif

#define SLOW_SPEED     100
#define MEDIUM_SPEED   150
#define FAST_SPEED     250

#define FADE_DELAY     3

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t dcMotor_init(dc_motor_t motor)
{

    if (motor == DC_MOTOR_1)
    {
        _initMotor(PIN_1_MOTOR_1, PIN_2_MOTOR_1, POWER_MOTOR_1);
        return ROBOT_OK;
    }
    else if (motor == DC_MOTOR_2)
    {
        _initMotor(PIN_1_MOTOR_2, PIN_2_MOTOR_2, POWER_MOTOR_2);
        return ROBOT_OK;
    }
    else
    {
        return ROBOT_ERR;
    }
}

robot_status_t dcMotor_run(dc_motor_t motor, uint8_t speed, dc_motor_dir_t dir)
{
    if (motor == DC_MOTOR_1)
    {
        _runDir(PIN_1_MOTOR_1, PIN_2_MOTOR_1, dir, speed);
    }
    else
    {
        _runDir(PIN_1_MOTOR_2, PIN_2_MOTOR_2, dir, speed);
    }

    return ROBOT_OK;
}

static void _runDir(uint8_t pin1, uint8_t pin2, dc_motor_dir_t dir, 
                    uint8_t speed)
{
    if (dir == CC_DIRECTION)
    {
        analogWrite(pin1, speed);
        analogWrite(pin2, STATIC_SPEED);
    }
    else
    {
        analogWrite(pin1, STATIC_SPEED);
        analogWrite(pin2, speed);
    }
}

static void _initMotor(uint8_t pin1, uint8_t pin2, uint8_t power)
{
    // Initialize the dc motor pins
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(power, OUTPUT);

    // Make sure all the motors driving pins are set LOW
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);

    // Power the motor driver
    digitalWrite(power, HIGH);

    for (uint8_t i = STATIC_SPEED; i < MAX_SPEED; i++)
    {
        analogWrite(pin1, i);
        delay(FADE_DELAY);
    }
    for (uint8_t i = MAX_SPEED - 1; i > STATIC_SPEED; i--)
    {
        analogWrite(pin1, i);
        delay(FADE_DELAY);
    }

    analogWrite(pin1, STATIC_SPEED);

    for (uint8_t i = STATIC_SPEED; i < MAX_SPEED; i++)
    {
        analogWrite(pin2, i);
        delay(FADE_DELAY);
    }
    for (uint8_t i = MAX_SPEED - 1; i > STATIC_SPEED; i--)
    {
        analogWrite(pin2, i);
        delay(FADE_DELAY);
    }

    analogWrite(pin2, STATIC_SPEED);
}