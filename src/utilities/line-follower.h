#ifndef LINE_FOLLOWER
#define LINE_FOLLOWER

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <stdint.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "robot-core/reflectance.h"

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
    RIGHT_LINE_FOLLOWER = RIGHT_REFLECTANCE,
    LEFT_LINE_FOLLOWER  = LEFT_REFLECTANCE
} line_follower_id_t;

typedef enum {
    ON_TAPE,
    OFF_TAPE
} line_follower_status_t;

typedef struct
{
    reflectance_t*           sensor;
    line_follower_status_t   status;
    line_follower_status_t   previousStatus;
    const line_follower_id_t id;
    bool                     initialized;
    uint16_t                 threshold;
} line_follower_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t lineFollower_init(line_follower_t* lineFollower,
                                 reflectance_t* sensor);

robot_status_t lineFollower_update(line_follower_t* lineFollower);

line_follower_t* lineFollower_get(line_follower_id_t id);

#endif // LINE_FOLLOWER