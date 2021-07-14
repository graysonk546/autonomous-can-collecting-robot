
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

typedef enum
{
    ROLLER_MOTOR
} dc_motor_one_id_t;

struct dc_motor_one_t
{
    const uint8_t pin;
    uint8_t speed;
    const dc_motor_one_id_t id;
    bool initialized;
};

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: ptr to dc_motor_one_t motor that has been initialized with a pin,
 *           and id
 * Effects:  returns ROBOT_OK if motor has been initialized without error, and
 *           ROBOT_ERR otherwise
 * Modifies: motor
 * ****************************************************************************/
robot_status_t dcMotorOne_init(dc_motor_one_t* motor);

/*******************************************************************************
 * Requires: ptr to dc_motor_one_t motor that has been initialized using
 *           dcMotorOne_init; speed ranges from 0-255 that maps linearly to to
 *           the min and max speeds of the unidirectional DC motor
 * Effects:  returns ROBOT_ERR if motor was not initialized using
 *           dcMotorOne_init, and returns ROBOT_OK otherwise
 * Modifies: motor
 * ****************************************************************************/
robot_status_t dcMotorOne_run(dc_motor_one_t* motor, uint8_t speed);

/*******************************************************************************
 * Requires: dc_motor_one_id_t id that corresponds to a given dc_motor_one_t
 *           motor
 * Effects:  returns a ptr to the corresponding dc_motor_one_t motor
 * Modifies: None
 * ****************************************************************************/
dc_motor_one_t* dcMotorOne_get(dc_motor_one_id_t id);

#endif // DC_MOTOR_ONE
