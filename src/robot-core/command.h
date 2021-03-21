
#ifndef COMMAND
#define COMMAND

/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

#include <pt.h>

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "utilities/util-vars.h"
#include "robot-cli/cli-command.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define COMMAND_PROMPT       "receptor> "
#define CMD_EOL              '\n'
#define CMD_EOL_STR          "\n"
#define STRING_EOL           '\0'
#define CMD_JSON             "JSON: "
#define COMMAND_BUFF_MAX_LEN 30
#define COMMAND_ARGS_MAX_LEN 4

/*******************************************************************************
*                               Structures
*******************************************************************************/

typedef struct {
    char line[COMMAND_BUFF_MAX_LEN];
    uint8_t index;
} command_line_t;

/*******************************************************************************
*                               Variables
*******************************************************************************/

/*******************************************************************************
*                               Function Declarations
*******************************************************************************/

receptor_status_t command_init();

bool command_readLine(char *byte);

void command_parseCommand(char *line);

void command_echoCommand(char *command);

struct pt* command_getThread();

command_line_t* command_getLine();

#endif // COMMAND