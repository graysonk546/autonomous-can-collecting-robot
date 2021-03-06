
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>
#include <pt.h>
#include <pt-sem.h>
#include <NewPing.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "robot-core/command.h"
#include "robot-control/line-following-controller.h"
#include "robot-control/can-collection-controller.h"
#include "robot-tasks/task-driving.h"
#include "robot-tasks/task-cli.h"
#include "robot-tasks/task-can-collection.h"
#include "robot-tasks/task-hopper-loading.h"
#include "robot-tasks/task-button.h"
#include "robot-tasks/task-return-vehicle-detection.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

// Task functions
static char _drivingTask(struct pt* thread);
static char _cliTask(struct pt* thread);
static char _clawTask(struct pt* thread);
static char _canCollectionTask(struct pt* thread);
static char _hopperLoadingTask(struct pt* thread);
static char _buttonTask(struct pt* thread);


/*******************************************************************************
*                               Constants
*******************************************************************************/

#define GROUND_DETECTED_DISTANCE 10  // cm
#define MIN_GROUND_DETECTOR_DISTANCE 2  // cm
#define MAX_GROUND_DETECTOR_DISTANCE 100  // cm

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

// Pointers for robot tasks
static robot_task_t* task_driving;
static robot_task_t* task_cli;
static robot_task_t* task_canCollection;
static robot_task_t* task_hopperLoading;
static robot_task_t* task_button;
static robot_task_t* task_returnVehicleDetection;

// Flags (in place of semaphores for the time being)
static bool flag;
static bool groundDetected;
static bool wasControllerCalledOnce;

// Ground detection
static NewPing groundDetector(PA11, PA12, MAX_GROUND_DETECTOR_DISTANCE);

/*******************************************************************************
*                               Setup and Loop
*******************************************************************************/

void setup()
{
    // Initilize flags
    flag = true;
    groundDetected = false;

    // Initialize peripherals
    if (taskCli_init() != ROBOT_OK)
    {

    }
    if (taskDriving_init() != ROBOT_OK)
    {

    }
    if (taskCanCollection_init() != ROBOT_OK)
    {
    }
    // if (taskHopperLoading_init() != ROBOT_OK)
    // {
    // }

    // }
    if (taskButton_init() != ROBOT_OK)
    {

    }
    // if (taskReturnVehicleDetection_init() != ROBOT_OK)
    // {

    // }
    
    // Get task references
    task_driving = taskDriving_getTask();
    task_cli = taskCli_getTask();
    task_canCollection = taskCanCollection_getTask();
    task_hopperLoading = taskHopperLoading_getTask();
    task_button = taskButton_getTask();
    task_returnVehicleDetection = taskReturnVehicleDetection_getTask();
}

void loop()
{
    if (task_button->taskFlag)
    {
        if (!groundDetected)
        {
            Serial.print("Ping = ");
            unsigned long dist = groundDetector.ping_cm();
            Serial.println(dist);
            if (dist < GROUND_DETECTED_DISTANCE && dist > MIN_GROUND_DETECTOR_DISTANCE)
            {
                groundDetected = true;
                canCollectionController_startUp();
                lineFollowingController_startUp();
                Serial.println("Ground successfully detected...");
            }
        }
        // else if (task_returnVehicleDetection->taskFlag)
        // {
        //     canCollectionController_shutDown();
        //     lineFollowingController_shutDown();
        //     servo_rotate(servo_get(HOPPER_ROTATION_SERVO), 180);
        //     delay(1000);
        //     servo_rotate(servo_get(HOPPER_DOOR_SERVO), 180);
        // }
    }
    // UNCOMMENT WHEN SONAR IS SETUP
    // if(!groundDetectedFlag)
    // {
    //     if (groundDetector.ping_cm() <= GROUND_DETECTED_DISTANCE)
    //     {
    //         groundDetectedFlag = true;
    //     }
    // }
    // else
    // {
    //     // call static function startupch
    //     _drivingTask(&task_driving->taskThread);
    //     _cliTask(&task_cli->taskThread);
    //     _clawTask(&task_claw->taskThread);
    //     _canCollectionTask(&task_canCollection->taskThread);
    // }

    // if (task_button->taskFlag)
    // {
    //     _hopperLoadingTask(&task_hopperLoading->taskThread);
    //     _canCollectionTask(&task_canCollection->taskThread);
    //     _drivingTask(&task_driving->taskThread);
    // }
    _drivingTask(&task_driving->taskThread);
    _canCollectionTask(&task_canCollection->taskThread);
    // _hopperLoadingTask(&task_hopperLoading->taskThread);
    _cliTask(&task_cli->taskThread);

}

/*******************************************************************************
*                               Functions
*******************************************************************************/

static PT_THREAD(_cliTask(struct pt* thread))
{
    // Static vars maintain value through context switches
    PT_BEGIN(thread);
    while (true)
    {
        // Critical section
        PT_WAIT_UNTIL(thread, Serial.available() > 0);
        char tmp = (char) Serial.read();
        if (command_readLine(&tmp))
        {
            command_line_t *line = command_getLine();
            command_echoCommand(line->line);
            command_parseCommand(line->line);
            Serial.print(COMMAND_PROMPT);
        }
    }
    PT_END(thread);
}

static PT_THREAD(_drivingTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_SEM_WAIT(thread, &task_driving->taskMutex);
        if (groundDetected)
        {
            lineFollowingController_spinOnce();
        }
    }
    PT_END(thread);
}

static PT_THREAD(_hopperLoadingTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_SEM_WAIT(thread, &task_hopperLoading->taskMutex);
    }
    PT_END(thread);
}

static PT_THREAD(_buttonTask(struct pt* thread))
{
    PT_BEGIN(thread);
    if (task_button->taskFlag)
    {
        Serial.println("Button On");
    }
    PT_END(thread);
}


static PT_THREAD(_canCollectionTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_SEM_WAIT(thread, &task_canCollection->taskMutex);
        if (groundDetected)
        {
            canCollectionController_spinOnce();
        }
    }
    PT_END(thread);
}