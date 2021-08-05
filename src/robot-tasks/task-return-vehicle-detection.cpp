/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <pt-sem.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "task-return-vehicle-detection.h"
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

static robot_task_t taskReturnVehicleDetection =
{
    .taskId      = RETURN_VEHICLE_DETECTION,
    .taskTime    = millis(),
    .taskFlag    = false
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t taskReturnVehicleDetection_init()
{
    pinMode(PIN_RETURN_VEHICLE_DETECTOR, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_RETURN_VEHICLE_DETECTOR), taskReturnVehicleDetection_ISR, 
                     FALLING);
    PT_INIT(&taskReturnVehicleDetection.taskThread);
    return ROBOT_OK;
}

void taskReturnVehicleDetection_ISR()
{
    taskReturnVehicleDetection.taskFlag = true;
    Serial.println("taskReturnVehicle_ISR() called");
}

robot_task_t* taskReturnVehicleDetection_getTask()
{
    return &taskReturnVehicleDetection;
}