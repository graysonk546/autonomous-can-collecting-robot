
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-driving.h"
#include "robot-core/dc-motor.h"
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

#ifdef UNO
static robot_task_t taskDriving =
{
    taskDriving.taskMutex,
    taskDriving.taskThread,
    taskDriving.taskId      = ROBOT_DRIVING,
    taskDriving.taskISR,
    taskDriving.taskTime    = millis()
};
#elif STM32
static robot_task_t taskDriving =
{
    .taskId   = ROBOT_DRIVING,
    .taskTime = millis()
};
#else
static robot_task_t taskDriving = 
{
    .taskId   = ROBOT_DRIVING,
    .taskTime = millis()
};
#endif

HardwareTimer* timer;

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskDriving_init()
{
    // if (dcMotor_init(DC_MOTOR_1) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // if(dcMotor_init(DC_MOTOR_2) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }

    //Intialize the timer for sampling the line follower signal
    timer = new HardwareTimer(TIM2);
    timer->setOverflow(1, HERTZ_FORMAT);
    timer->refresh();

    timer->attachInterrupt(taskDriving_ISR);
    timer->resume();

    // Initialize the driving task pt thread
    PT_INIT(&taskDriving.taskThread);
    // Initialize the driving task pt sem
    PT_SEM_INIT(&taskDriving.taskMutex, 0);
    return ROBOT_OK;
}

void taskDriving_ISR()
{
    // if (millis() - taskDriving.taskTime)
    // {
    //     PT_SEM_SIGNAL(&taskDriving.taskThread, &taskDriving.taskMutex);
    //     taskDriving.taskTime = millis();
    // }

    PT_SEM_SIGNAL(&taskDriving.taskThread, &taskDriving.taskMutex);
}

robot_task_t* taskDriving_getTask()
{
    return &taskDriving;
}
