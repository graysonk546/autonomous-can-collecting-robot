#ifndef SERVO
#define SERVO

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Servo.h>
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

#define MAX_ANGLE 180
#define MIN_ANGLE 0

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef enum
{
    HOPPER_ROTATION_SERVO
} servo_id_t;

typedef struct
{
    Servo            motor;
    const uint8_t    pin;
    uint8_t          angle;
    const servo_id_t id;
    bool             initialized;
} servo_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: ptr to servo_t servo that has been initialized with a pin, and id
 * Effects:  returns ROBOT_OK if servo has been initialized without error, and
 *           ROBOT_ERR otherwise
 * Modifies: servo.angle
 * ****************************************************************************/
robot_status_t servo_init(servo_t* servo);

/*******************************************************************************
 * Requires: ptr to servo_t that has been initialized using servo_init; angle
 *           ranges from 0-180
 * Effects:  returns ROBOT_ERR if servo was not initialized using
 *           servo_init, and returns ROBOT_OK otherwise
 * Modifies: servo.angle
 * ****************************************************************************/
robot_status_t servo_rotate(servo_t* servo, uint8_t angle);

/*******************************************************************************
 * Requires: servo_id_T id that corresponds to a given servo_t servo
 * Effects:  returns a ptr to the corresponding servo_t servo
 * Modifies: None
 * ****************************************************************************/
servo_t* servo_get(servo_id_t id);

#endif // SERVO
