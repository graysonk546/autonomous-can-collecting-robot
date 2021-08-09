/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "reflectance.h"
#include "utilities/robot-config.h"

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
static reflectance_t reflectanceArr[] =
{
    [LEFT_REFLECTANCE] = 
    {
        .pin         = PIN_LEFT_LINE_FOLLOWING_IR_SENSOR,
        .id          = LEFT_REFLECTANCE,
        .initialized = false
    },
    [RIGHT_REFLECTANCE] = 
    {
        .pin         = PIN_RIGHT_LINE_FOLLOWING_IR_SENSOR,
        .id          = RIGHT_REFLECTANCE,
        .initialized = false
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t reflectance_init(reflectance_t* sensor)
{
    pinMode(sensor->pin, INPUT);
    sensor->initialized = true;
    return ROBOT_OK;
}

robot_status_t reflectance_read(reflectance_t* sensor)
{
    sensor->value = (uint16_t) analogRead(sensor->pin);
    return ROBOT_OK;
}

reflectance_t* reflectance_get(reflectance_id_t id)
{
    return &reflectanceArr[id];
}