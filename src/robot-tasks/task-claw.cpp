
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-claw.h"
#include "robot-core/sonar.h"
#include "utilities/util-vars.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define CLAW_INT_PIN PB11
#define CLAW_TIMEOUT 500

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

// Default thread and not directly interrupt driven
#ifdef UNO
static robot_task_t taskClaw =
{
    taskClaw.taskMutex,
    taskClaw.taskThread,
    taskClaw.taskId      = ROBOT_CLAW,
    taskClaw.taskISR,
    taskClaw.taskTime    = millis()
};
#elif STM32
static robot_task_t taskClaw =
{
    .taskId   = ROBOT_CLAW,
    .taskTime = millis()
};
#else
static robot_task_t taskClaw = 
{
    .taskId   = ROBOT_CLAW,
    .taskTime = millis()
};
#endif

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskClaw_init()
{
    // Initialize the periphs used in this task
    if (sonar_init() != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    // Initialize the interrupt pin
    pinMode(CLAW_INT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLAW_INT_PIN), 
                    taskClaw_ISR, RISING);
    // Initialize the claw task pt thread
    PT_INIT(&taskClaw.taskThread);
    // Initialize the claw task pt sem
    PT_SEM_INIT(&taskClaw.taskMutex, 0);
    return ROBOT_OK;
}

robot_task_t* taskClaw_getTask()
{
    return &taskClaw;
}

void taskClaw_ISR()
{
    if ((millis() - taskClaw.taskTime) > CLAW_TIMEOUT)
    {
        PT_SEM_SIGNAL(&taskClaw.taskThread, &taskClaw.taskMutex);
        taskClaw.taskTime = millis();
    }
}