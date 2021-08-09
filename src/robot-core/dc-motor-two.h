
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

typedef enum
{
    CW_DIRECTION,
    CCW_DIRECTION
} rotation_dir_t;

typedef enum
{
    RIGHT_DRIVING_MOTOR,
    LEFT_DRIVING_MOTOR,
    ROLLER_DRIVING_MOTOR
} dc_motor_two_id_t;

struct dc_motor_two_t
{
    const uint8_t cw_pin;
    const uint8_t ccw_pin;
    rotation_dir_t direction;
    uint8_t speed;
    const dc_motor_two_id_t id;
    bool initialized;
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: ptr to dc_motor_two_t motor that has been initialized with a
 *           cw_pin, ccw_pin, direction, speed and id
 * Effects:  returns ROBOT_OK if motor has been initialized without error, and
 *           ROBOT_ERR otherwise
 * Modifies: motor
 * ****************************************************************************/
robot_status_t dcMotorTwo_init(dc_motor_two_t* motor);

/*******************************************************************************
 * Requires: ptr to dc_motor_two_t motor that has been initialized using
 *           dcMotorTwo_init; speed ranges from 0-255 that maps linearly to to
 *           the min and max speeds of the biidirectional DC motor; direction
 *           is either CW_DIRECTION or CCW_DIRECTION
 * Effects:  returns ROBOT_ERR if motor was not initialized using
 *           dcMotorTwo_init, and returns ROBOT_OK otherwise
 * Modifies: motor
 * ****************************************************************************/
robot_status_t dcMotorTwo_run(dc_motor_two_t* motor, uint8_t speed,
                             rotation_dir_t direction);

/*******************************************************************************
 * Requires: dc_motor_two_id_t id that corresponds to a given dc_motor_two_t
 *           motor
 * Effects:  returns a ptr to the corresponding dc_motor_two_t motor
 * Modifies: None
 * ****************************************************************************/
dc_motor_two_t* dcMotorTwo_get(dc_motor_two_id_t id);

#endif // DC_MOTOR_TWO