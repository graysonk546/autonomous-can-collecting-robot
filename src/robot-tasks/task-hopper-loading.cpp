
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
#include "robot-core/servo.h"
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

static robot_task_t taskHopperLoading =
{
    .taskId   = ROBOT_HOPPER_LOADING,
    .taskTime = millis()
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskHopperLoading_init()
{
    // if (reflectance_init(reflectance_get(RIGHT_REFLECTANCE)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // else if (reflectance_init(reflectance_get(LEFT_REFLECTANCE)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // else if (dcMotorTwo_init(dcMotorTwo_get(RIGHT_DRIVING_MOTOR)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // else if (dcMotorTwo_init(dcMotorTwo_get(LEFT_DRIVING_MOTOR)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // } 
    // else if (lineFollowingController_init(reflectance_get(RIGHT_REFLECTANCE), 
    //                                       reflectance_get(LEFT_REFLECTANCE), 
    //                                       dcMotorTwo_get(RIGHT_DRIVING_MOTOR), 
    //                                       dcMotorTwo_get(LEFT_DRIVING_MOTOR)) != 
    //                                       ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }

    servo_motor_t* servo = servo_get(HOPPER_LOADING_SERVO);

    if (servo_init(servo) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }



    // //Intialize the timer for sampling the line follower signal
    // timer = new HardwareTimer(TIM2);
    // timer->setOverflow(2000, HERTZ_FORMAT);
    // timer->refresh();
    // timer->attachInterrupt(taskDriving_ISR);
    // timer->resume();

    // // Initialize the driving task pt thread
    // PT_INIT(&taskDriving.taskThread);
    // // Initialize the driving task pt sem
    // PT_SEM_INIT(&taskDriving.taskMutex, 0);
    return ROBOT_OK;
}

void taskHopperLoading_ISR()
{

    PT_SEM_SIGNAL(&taskHopperLoading.taskThread, &taskHopperLoading.taskMutex);
}

robot_task_t* taskHopperLoading_getTask()
{
    return &taskHopperLoading;
}
