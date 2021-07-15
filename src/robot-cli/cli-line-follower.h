#ifndef CLI_LINE_FOLLOWER
#define CLI_LINE_FOLLOWER
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "utilities/util-vars.h"
#include "utilities/line-follower.h"

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

/*******************************************************************************
*                               Functions
*******************************************************************************/

cli_status_t cliLineFollower_init(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollower_setThreshold(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollower_getThreshold(uint8_t argNumber, char* args[]);

#define LINE_FOLLOWER_COMMANDS                                                                                              \
    {cliLineFollower_init,          "line-follow-init",        "<periph>",          "init the line follower periph", 1, 1}, \
    {cliLineFollower_getThreshold,  "line-follow-get-thresh",  "<periph>",          "get line follower threshold",   1, 1}, \
    {cliLineFollower_setThreshold,  "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   2, 2},
#endif // CLI_