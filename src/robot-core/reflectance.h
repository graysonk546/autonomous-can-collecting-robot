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
    LEFT_REFLECTANCE,
    RIGHT_REFLECTANCE
} reflectance_id_t;

typedef struct {
    uint8_t          pin;
    reflectance_id_t id;
    uint16_t         value;
    bool             initialized;
} reflectance_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

/*******************************************************************************
 * Requires: ptr to reflectance_t sensor that has been initialized with a pin,
 *           id, and value
 * Effects:  returns ROBOT_OK if sensor has been initialized without error, and
 *           ROBOT_ERR otherwise
 * Modifies: sensor.pin, sensor.value, sensor.initialized
 * ****************************************************************************/
robot_status_t reflectance_init(reflectance_t* sensor);

/*******************************************************************************
 * Requires: ptr to reflectance_t sensor that has been initialized using 
 *           reflectance_init
 * Effects:  returns ROBOT_ERR if motor was not initialized using
 *           reflectance_init, and returns ROBOT_OK otherwise
 * Modifies: sensor.value
 * ****************************************************************************/
robot_status_t reflectance_read(reflectance_t* sensor);

/*******************************************************************************
 * Requires: reflectance_id_t that corresponds to a given reflectance_t sensor
 * Effects:  returns a ptr to the corresponding reflectance_t sensor
 * Modifies: None
 * ****************************************************************************/
reflectance_t* reflectance_get(reflectance_id_t id);

#endif // REFLECTANCE