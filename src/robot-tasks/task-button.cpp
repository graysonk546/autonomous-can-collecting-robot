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
    // if(dcMotorOne_init(dcMotorOne_get(ROLLER_MOTOR)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // else if (canCollectionController_init(dcMotorOne_get(ROLLER_MOTOR)) !=
    //          ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }

    // taskCanCollectionTimer = new HardwareTimer(TIM3);
    // taskCanCollectionTimer->setOverflow(100, HERTZ_FORMAT);
    // taskCanCollectionTimer->refresh();
    // taskCanCollectionTimer->attachInterrupt(taskCanCollection_ISR);
    // taskCanCollectionTimer->resume();

    pinMode(PIN_BUTTON, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), taskButton_ISR, 
                     FALLING);

    PT_INIT(&taskButton.taskThread);
    // PT_SEM_INIT(&taskButton.taskMutex, 0);
    return ROBOT_OK;
}

void taskButton_ISR()
{
    taskButton.taskFlag = !taskButton.taskFlag;
<<<<<<< Updated upstream
    Serial.println("Button pressed...");
=======
    Serial.print("Button task flag = ");
    Serial.println(taskButton.taskFlag);
>>>>>>> Stashed changes
}

robot_task_t* taskButton_getTask()
{
    return &taskButton;
}