
#ifndef DC_MOTOR_TWO
#define DC_MOTOR_TWO

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

typedef enum {
    CW_DIRECTION,
    CCW_DIRECTION
} rotation_dir_t;

struct dc_motor_two_t
{
    uint8_t cw_pin;
    uint8_t ccw_pin;
    rotation_dir_t direction;
    uint8_t speed;
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
robot_status_t dcMotorTwo_init(dc_motor_two_t* motor, uint8_t cw_pin_number,
                              uint8_t ccw_pin_number);

/*******************************************************************************
 * Requires: speed ranging from 0-255 that maps linearly to to the min and max
 *           speeds of the unidirectional DC motor
 * Effects:  Returns robot_status_t indicating state of motor after function
 *           call
 * Modifies: self
 * ****************************************************************************/
robot_status_t dcMotorTwo_run(dc_motor_two_t* motor, uint8_t speed,
                             rotation_dir_t direction);

#endif // DC_MOTOR_TWO