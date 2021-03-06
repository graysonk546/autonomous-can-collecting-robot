#ifndef TASK_HOPPER_LOADING
#define TASK_HOPPER_LOADING

/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>

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
robot_status_t taskHopperLoading_init();

/*******************************************************************************
 * Requires: None
 * Effects:  None
 * Modifies: Takes and releases pt_sem mutex in robot_task_t for driving
 * ****************************************************************************/
void taskHopperLoading_ISR();

/*******************************************************************************
 * Requires: None
 * Effects:  Returns a robot_task_t pointer to the driving task
 * Modifies: None
 * ****************************************************************************/
robot_task_t* taskHopperLoading_getTask();

#endif // TASK_HOPPER_LOADING