
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
#include "robot-core/reflectance.h"
#include "robot-control/line-following-controller.h"
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
    if (reflectance_init(reflectance_get(RIGHT_REFLECTANCE)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    else if (reflectance_init(reflectance_get(LEFT_REFLECTANCE)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    else if (dcMotorTwo_init(dcMotorTwo_get(RIGHT_DRIVING_MOTOR)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    else if (dcMotorTwo_init(dcMotorTwo_get(LEFT_DRIVING_MOTOR)) != ROBOT_OK)
    {
        return ROBOT_ERR;
    } 
    else if (lineFollowingController_init(reflectance_get(RIGHT_REFLECTANCE), 
                                          reflectance_get(LEFT_REFLECTANCE), 
                                          dcMotorTwo_get(RIGHT_DRIVING_MOTOR), 
                                          dcMotorTwo_get(LEFT_DRIVING_MOTOR)) != 
                                          ROBOT_OK)
    {
        return ROBOT_ERR;
    }

    //Intialize the timer for sampling the line follower signal
    timer = new HardwareTimer(TIM2);
    timer->setOverflow(2000, HERTZ_FORMAT);
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
<<<<<<< HEAD
=======
    // if (millis() - taskDriving.taskTime)
    // {
    //     PT_SEM_SIGNAL(&taskDriving.taskThread, &taskDriving.taskMutex);
    //     taskDriving.taskTime = millis();
    // }

>>>>>>> master
    PT_SEM_SIGNAL(&taskDriving.taskThread, &taskDriving.taskMutex);
}

robot_task_t* taskDriving_getTask()
{
    return &taskDriving;
}
