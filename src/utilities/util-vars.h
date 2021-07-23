#ifndef UTIL_VARS_H
#define UTIL_VARS_H

/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define NUM_DRIVING_MOTORS 2
#define NUM_LINE_FOLLOWING_SENSORS 2

/*******************************************************************************
*                                 Macros
*******************************************************************************/

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? \
              (low) : (x)))

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef void (*ISR_func_t)(void);

typedef enum {
    ROBOT_OK,
    ROBOT_ERR
} robot_status_t;

typedef enum {
    ROBOT_CLI,
    ROBOT_DRIVING,
    ROBOT_CLAW,
    ROBOT_CAN_COLLECTION,
    ROBOT_SKY_CRANE
} robot_task_id_t;

typedef struct{
    struct pt_sem   taskMutex;
    struct pt       taskThread;
    robot_task_id_t taskId;
    ISR_func_t      taskISR;
    unsigned long   taskTime;
} robot_task_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Functions
*******************************************************************************/

#endif // UTIL_VARS_H