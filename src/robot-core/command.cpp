/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <pt.h>
#include <Arduino.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "command.h"
#include "robot-cli/command-listing.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define SERIAL_TIMEOUT_MS 5000

#ifdef UNO
#define BAUD_RATE 9600
#elif STM32
#define BAUD_RATE 115200
#else
#define BAUD_RATE 115200
#endif

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

// static struct pt commandThread;

#ifdef STM32
static command_line_t commandLine = {
    .index = 0
};
#elif UNO
static command_line_t commandLine = {
    commandLine.index = 0
};
#else
static command_line_t commandLine = {
    .index = 0
};
#endif

// Might want to log command line entries
static char* args[COMMAND_ARGS_MAX_LEN];
static char* tokCommand[(COMMAND_ARGS_MAX_LEN + 1)];

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t command_init()
{
    // Begin the serial connection
    Serial.begin(BAUD_RATE);
    while(!Serial)
    {
        if (millis() > SERIAL_TIMEOUT_MS)
        {
            return ROBOT_ERR;
        }
    }
    Serial.println(F("Initialized serial port!"));
    Serial.print(COMMAND_PROMPT);

    // Initialize pt structure
    // PT_INIT(&commandThread);
    return ROBOT_OK;
}

bool command_readLine(char *byte)
{
    if (*byte == CMD_EOL)
    {
        commandLine.line[commandLine.index] = STRING_EOL;
        commandLine.index = 0;
        return true;
    }
    else
    {
        commandLine.line[commandLine.index++] = *byte;
        return false;
    }
}

void command_parseCommand(char* line)
{
    // Tokenize the line with spaces as the delimiter
    char* tok = (char*) strtok(line, " ");
    uint8_t i = 0;
    while (tok != NULL && i < COMMAND_BUFF_MAX_LEN)
    {
        tokCommand[i] = tok;
        tok = strtok(NULL, " ");
        i++;
    }

    // Find a match for the command entered
    uint8_t j = 0;
    while (strcmp(commandArr[j].command, LIST_TERMINATOR) != 0)
    {
        if (strcmp(commandArr[j].command, tokCommand[0]) == 0)
        {
            break;
        }
        j++;
    }

    // Process the command entered
    if (strcmp(line, "") != 0)
    {
        if (strcmp(commandArr[j].command, LIST_TERMINATOR) == 0)
        {
            Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\":"
                         " \"invalid command\"}" CMD_EOL_STR));
        }
        else if ((i - 1) > commandArr[j].maxParam)
        {
            Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"too"
                         " many args\"}" CMD_EOL_STR));
        }
        else if ((i - 1) < commandArr[j].minParam)
        {
            Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"too"
                         " few args\"}" CMD_EOL_STR));
        }
        else
        {
            if (j == 0)
            {
                // Call the function corresponding to the command with no args
                cli_func_t func = commandArr[j].function;
                func (0, NULL);
            }
            else
            {
                // Package the args into a char* array
                for (uint8_t k = 1; k < i; k++)
                {
                    args[(k - 1)] = tokCommand[k];
                }

                // Call the function corresponding to the comannd with args
                cli_func_t func = commandArr[j].function;
                func  (i, args);
            }
        }
    }
    memset(tokCommand, '\0', sizeof(tokCommand));
    memset(args, '\0', sizeof(args));
}

void command_echoCommand(char *line)
{
    uint8_t i = 0;
    while (line[i] != STRING_EOL)
    {
        Serial.print(line[i]);
        i++;
    }
    Serial.print(CMD_EOL);
}

command_line_t* command_getLine()
{
    return &commandLine;
}