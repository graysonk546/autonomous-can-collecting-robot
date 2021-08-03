/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-can-collection.h"
#include "robot-core/dc-motor-two.h"
#include "robot-control/can-collection-controller.h"
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

static robot_task_t taskCanCollection =
{
    taskCanCollection.taskMutex,
    taskCanCollection.taskThread,
    taskCanCollection.taskId      = ROBOT_CAN_COLLECTION,
    taskCanCollection.taskISR,
    taskCanCollection.taskTime    = millis()
};

HardwareTimer* taskCanCollectionTimer;

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskCanCollection_init()
{
    if(dcMotorTwo_init(dcMotorTwo_get(ROLLER_DRIVING_MOTOR)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    else if (rotarySpeedEncoder_init(
             rotarySpeedEncoder_get(ROLLER_SPEED_ENCODER)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    else if (canCollectionController_init(dcMotorTwo_get(ROLLER_DRIVING_MOTOR),
             rotarySpeedEncoder_get(ROLLER_SPEED_ENCODER)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }

    taskCanCollectionTimer = new HardwareTimer(TIM3);
    taskCanCollectionTimer->setOverflow(100, HERTZ_FORMAT);
    taskCanCollectionTimer->refresh();
    taskCanCollectionTimer->attachInterrupt(taskCanCollection_ISR);
    taskCanCollectionTimer->resume();

    PT_INIT(&taskCanCollection.taskThread);
    PT_SEM_INIT(&taskCanCollection.taskMutex, 0);
    Serial.println("taskCanCollection_init() called...");
    return ROBOT_OK;
}

void taskCanCollection_ISR()
{
    PT_SEM_SIGNAL(&taskCanCollection.taskThread, &taskCanCollection.taskMutex);
}

robot_task_t* taskCanCollection_getTask()
{
    return &taskCanCollection;
}
