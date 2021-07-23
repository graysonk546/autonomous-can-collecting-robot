
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
#include "robot-core/sonar.h"
#include "robot-control/line-following-controller.h"
#include "robot-control/can-collection-controller.h"
#include "robot-tasks/task-driving.h"
#include "robot-tasks/task-cli.h"
#include "robot-tasks/task-claw.h"
#include "robot-tasks/task-can-collection.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

// Task functions
static char _drivingTask(struct pt* thread);
static char _cliTask(struct pt* thread);
static char _clawTask(struct pt* thread);
static char _canCollectionTask(struct pt* thread);

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

// Pointers for robot tasks
static robot_task_t* task_driving;
static robot_task_t* task_cli;
static robot_task_t* task_claw;
static robot_task_t* task_canCollection;

// Flags (in place of semaphores for the time being)
static bool flag;

/*******************************************************************************
*                               Setup and Loop
*******************************************************************************/

void setup()
{
    // Initilize flags
    flag = true;

    // Initialize peripherals
    if (taskCli_init() != ROBOT_OK)
    {

    }
    if (taskDriving_init() != ROBOT_OK)
    {

    }
    if (taskClaw_init() != ROBOT_OK)
    {
        // TODO: Figure out some sort of error handler
    }
    if (taskCanCollection_init() != ROBOT_OK)
    {

    }

    // init sonar
    
    // Get task references
    task_driving = taskDriving_getTask();
    task_cli = taskCli_getTask();
    task_claw = taskClaw_getTask();
    task_canCollection = taskCanCollection_getTask();
}

void loop()
{
    // Looping achieves thread scheduling

    // call static function startupch
    _drivingTask(&task_driving->taskThread);
    _cliTask(&task_cli->taskThread);
    _clawTask(&task_claw->taskThread);
    _canCollectionTask(&task_canCollection->taskThread);
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
        lineFollowingController_spinOnce();
    }
    PT_END(thread);
}

static PT_THREAD(_clawTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_SEM_WAIT(thread, &task_claw->taskMutex);
        Serial.println("Claw!");
        // Critical section
    }
    PT_END(thread);
}

static PT_THREAD(_canCollectionTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while (true)
    {
        PT_SEM_WAIT(thread, &task_canCollection->taskMutex);
        canCollectionController_spinOnce();
    }
    PT_END(thread);
}