
#ifndef DC_MOTOR_ONE
#define DC_MOTOR_ONE

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <stdint.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "utilities/util-vars.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define MAX_SPEED    255
#define STATIC_SPEED 0

/*******************************************************************************
*                               Structures
*******************************************************************************/

struct dc_motor_one_t
{
    uint8_t pin;
    uint8_t speed;
    motor_id_t id;
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: pin_number corresponding to the PWM output to the unidirectional DC
 *           motor
 * Effects:  Returns dc_motor_1d_t pointer
 * Modifies: None
 * ****************************************************************************/
robot_status_t dcMotorOne_init(dc_motor_one_t* motor);

/*******************************************************************************
 * Requires: speed ranging from 0-255 that maps linearly to to the min and max
 *           speeds of the unidirectional DC motor
 * Effects:  Returns robot_status_t indicating state of motor after function
 *           call
 * Modifies: self
 * ****************************************************************************/
robot_status_t dcMotorOne_run(dc_motor_one_t* motor, uint8_t speed);

#endif // DC_MOTOR_ONE


// dc_motor_one_t ROLLER_MOTOR;
// dcMotorOne_init(ROLLER_MOTOR, ROLLER_MOTOR_PIN)
// ...
// dcMotorOne_run(ROLLER_MOTOR, 238)