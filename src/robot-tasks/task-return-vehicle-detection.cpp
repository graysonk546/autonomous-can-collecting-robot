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
#include "robot-core/servo.h"

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
    // if (servo_init(servo_get(HOPPER_ROTATION_SERVO)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    // if (servo_init(servo_get(HOPPER_DOOR_SERVO)) != ROBOT_OK)
    // {
    //     return ROBOT_ERR;
    // }
    pinMode(PIN_RETURN_VEHICLE_DETECTOR, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(PIN_RETURN_VEHICLE_DETECTOR), taskReturnVehicleDetection_ISR, 
                     FALLING);
    PT_INIT(&taskReturnVehicleDetection.taskThread);
    return ROBOT_OK;
}

void taskReturnVehicleDetection_ISR()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (digitalRead(PIN_RETURN_VEHICLE_DETECTOR) != HIGH)
        {
            return;
        }
    }
    taskReturnVehicleDetection.taskFlag = true;
    servo_init(servo_get(HOPPER_ROTATION_SERVO));
    servo_init(servo_get(HOPPER_DOOR_SERVO));
    Serial.println("taskReturnVehicle_ISR() called");
}

robot_task_t* taskReturnVehicleDetection_getTask()
{
    return &taskReturnVehicleDetection;
}