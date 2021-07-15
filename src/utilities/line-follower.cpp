/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "line-follower.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

inline static void _updateStatus(line_follower_t* lineFollower);

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static line_follower_t lineFollowerArr[] =
{
    [RIGHT_LINE_FOLLOWER] =
    {
        .sensor = 0,
        .status = ON_TAPE,
        .previousStatus = ON_TAPE,
        .id = RIGHT_LINE_FOLLOWER,
        .initialized = false

    },
    [LEFT_LINE_FOLLOWER] =
    {
        .sensor = 0,
        .status = ON_TAPE,
        .previousStatus = ON_TAPE,
        .id = LEFT_LINE_FOLLOWER,
        .initialized = false
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t lineFollower_init(line_follower_t* lineFollower,
                                 reflectance_t* sensor)
{
    if (!sensor->initialized) return ROBOT_ERR;
    lineFollower->sensor = sensor;
    _updateStatus(lineFollower);
    return ROBOT_OK;
}

robot_status_t lineFollower_update(line_follower_t* lineFollower)
{
    if (!lineFollower->initialized) return ROBOT_ERR;
    _updateStatus(lineFollower);
    return ROBOT_OK;
}

line_follower_t* lineFollower_get(line_follower_id_t id)
{
    return &lineFollowerArr[id];
}

inline static void _updateStatus(line_follower_t* lineFollower)
{
    lineFollower->previousStatus = lineFollower->status;
    if (lineFollower->sensor->value >= 512)
    {
        lineFollower->status = ON_TAPE;
    }
    else
    {
        lineFollower->status = OFF_TAPE;
    }
    
}