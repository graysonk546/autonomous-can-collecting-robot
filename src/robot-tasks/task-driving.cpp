
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

#define DRIVING_INT_TIMER TIM1
#define DRIVING_TIMER_CH 2
// TODO: Make this much faster...
#define DRIVING_SAMP_PERIOD 50000 // 50 ms sampling period

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static HardwareTimer* pwmTimer;

#ifdef UNO
static robot_task_t taskDriving =
{
    taskDriving.taskMutex,
    taskDriving.taskThread,
    taskDriving.taskId      = ROBOT_DRIVING,
    taskDriving.taskISR,
    taskDriving.taskTime
};
#elif STM32
static robot_task_t taskDriving =
{
    .taskId   = ROBOT_DRIVING,
};
#else
static robot_task_t taskDriving = 
{
    .taskId   = ROBOT_DRIVING,
};
#endif

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskDriving_init()
{
    if (dcMotor_init(DC_MOTOR_1) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }
    if(dcMotor_init(DC_MOTOR_2) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }

    // Initialize the timer interrupt for sampling
    pwmTimer =  new HardwareTimer(DRIVING_INT_TIMER);
    pwmTimer->pause();
    pwmTimer->setMode(DRIVING_TIMER_CH, TIMER_DISABLED);
    pwmTimer->setOverflow(50000, MICROSEC_FORMAT);
    // TODO: Understand what this does?
    pwmTimer->setCaptureCompare(DRIVING_TIMER_CH, MICROSEC_COMPARE_FORMAT);
    pwmTimer->attachInterrupt(taskDriving_ISR);
    pwmTimer->refresh();
    pwmTimer->resume();

    // Initialize the driving task pt thread
    PT_INIT(&taskDriving.taskThread);
    // Initialize the driving task pt sem
    PT_SEM_INIT(&taskDriving.taskMutex, 0);

    return ROBOT_OK;
}

void taskDriving_ISR()
{
    PT_SEM_SIGNAL(&taskDriving.taskThread, &taskDriving.taskMutex);
}

robot_task_t* taskDriving_getTask()
{
    return &taskDriving;
}
