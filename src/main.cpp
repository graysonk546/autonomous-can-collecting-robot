
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "robot-core/command.h"
#include "robot-core/accelerometer.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

// Task functions
static char _commandTask(struct pt *thread);
static char _accelerometerTask(struct pt *thread);

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

// Pointers for task threads
static struct pt* pt_command;
static struct pt* pt_accelerometer;

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
    command_init();

    // Get thread references
    pt_command = command_getThread();
    pt_accelerometer = accelerometer_getThread();
}

void loop()
{
    // Looping achieves thread scheduling
    _commandTask(pt_command);
    _accelerometerTask(pt_accelerometer);
}

/*******************************************************************************
*                               Functions
*******************************************************************************/

static PT_THREAD(_commandTask(struct pt *thread))
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

static PT_THREAD(_accelerometerTask(struct pt* thread))
{
    PT_BEGIN(thread);
    while(true)
    {
        PT_WAIT_UNTIL(thread, flag == false);
    }
    PT_END(thread);
}
