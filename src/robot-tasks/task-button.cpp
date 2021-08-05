/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-button.h"
#include "utilities/util-vars.h"
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

static robot_task_t taskButton =
{
    .taskId      = ROBOT_TASK_BUTTON,
    .taskTime    = millis(),
    .taskFlag    = false
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskButton_init()
{
    pinMode(PIN_BUTTON, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), taskButton_ISR, 
                     FALLING);
    PT_INIT(&taskButton.taskThread);
    return ROBOT_OK;
}

void taskButton_ISR()
{
    taskButton.taskFlag = !taskButton.taskFlag;
    Serial.print("Button task flag = ");
    Serial.println(taskButton.taskFlag);
}

robot_task_t* taskButton_getTask()
{
    return &taskButton;
}