
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-cli.h"
#include "robot-core/command.h"
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

// Default thread and not directly interrupt driven
#ifdef UNO
static robot_task_t taskCli =
{
    taskCli.taskMutex,
    taskCli.taskThread,
    taskCli.taskId      = ROBOT_CLI,
    taskCli.taskISR
};
#elif STM32
static robot_task_t taskCli =
{
    .taskId = ROBOT_CLI
};
#else
static robot_task_t taskCli = 
{
    .taskId = ROBOT_CLI
};
#endif

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskCli_init()
{
    // Initialize the periphs used in this task
    if (command_init() != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    // Initialize the driving task pt thread
    PT_INIT(&taskCli.taskThread);
    // Initialize the driving task pt sem
    PT_SEM_INIT(&taskCli.taskMutex, 0);
    return ROBOT_OK;
}

robot_task_t* taskCli_getTask()
{
    return &taskCli;
}
