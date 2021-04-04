
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>
#include <pt.h>
#include <pt-sem.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "robot-core/command.h"
#include "robot-core/dc-motor.h"
#include "robot-tasks/task-driving.h"
#include "robot-tasks/task-cli.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

// Task functions
static char _drivingTask(struct pt* thread);
static char _cliTask(struct pt* thread);

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define TEN_SEC_MILLIS 1000

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

// Pointers for robot tasks
static robot_task_t* task_driving;
static robot_task_t* task_cli;

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
        // TODO: Figure out some sort of error handler
    }
    
    // Get task references
    task_driving = taskDriving_getTask();
    task_cli = taskCli_getTask();
}

void loop()
{
    // Looping achieves thread scheduling
    _drivingTask(&task_driving->taskThread);
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
    while(true)
    {
        PT_WAIT_UNTIL(thread, flag == false);
    }
    PT_END(thread);
}