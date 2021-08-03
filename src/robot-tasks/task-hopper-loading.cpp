
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-hopper-loading.h"
#include "robot-core/servo.h"
#include "utilities/util-vars.h"
#include "utilities/robot-config.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

static uint16_t CAN_LOADING_SENSOR_DELAY = 100;

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
    servo_motor_t* servo = servo_get(HOPPER_LOADING_SERVO);

    if (servo_init(servo) != ROBOT_OK)
    {
        return ROBOT_ERR;
    }

    // Setup can detector pin and interrupt
    pinMode(PIN_CAN_DETECTOR, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_CAN_DETECTOR), 
                    taskHopperLoading_ISR, RISING);

    // Initialize the driving task pt thread
    PT_INIT(&taskHopperLoading.taskThread);
    // Initialize the driving task pt sem
    PT_SEM_INIT(&taskHopperLoading.taskMutex, 0);

    // Update the task time
    taskHopperLoading.taskTime = millis();

    return ROBOT_OK;
}

void taskHopperLoading_ISR()
{

    Serial.println("taskHopperLoading_ISR() called");
    PT_SEM_SIGNAL(&taskHopperLoading.taskThread, &taskHopperLoading.taskMutex);
    taskHopperLoading.taskTime = millis();
}

robot_task_t* taskHopperLoading_getTask()
{
    return &taskHopperLoading;
}
