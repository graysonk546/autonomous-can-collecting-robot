#ifndef REFLECTANCE
#define REFLECTANCE

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>

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

/*******************************************************************************
*                               Structures
*******************************************************************************/
typedef enum {
    RIGHT_REFLECTANCE,
    LEFT_REFLECTANCE
} reflectance_id_t;

typedef struct {
    uint8_t pin;
    reflectance_id_t id;
    uint16_t value;
    bool initialized;
} reflectance_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: None
 * Effects:  Returns robot_status_t indicating state of initialization
 * Modifies: None
 * ****************************************************************************/
robot_status_t reflectance_init();

/*******************************************************************************
 * Requires: Pointer to an intialized reflectance_t
 * Effects:  Returns robot_status_t indicating the status of the read
 * Modifies: Updates the value field of the reflectance_t
 * ****************************************************************************/
robot_status_t reflectance_read(reflectance_t* sensor);

/*******************************************************************************
 * Requires: reflectance_id_t indicating the desired reflectance_t
 * Effects:  Returns pointer to the corresponding reflectance_t
 * Modifies: None
 * ****************************************************************************/
reflectance_t* reflectance_get(reflectance_id_t id);

#endif // REFLECTANCE