#ifndef CLI_LINE_FOLLOWING_CONTROLLER
#define CLI_LINE_FOLLOWING_CONTROLLER
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "utilities/util-vars.h"
#include "utilities/line-following-controller.h"

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

cli_status_t cliLineFollowingController_getKp(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setKp(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getKd(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setKd(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getKi(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setKi(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getGain(uint8_t argNumber, 
                                                char* args[]);

cli_status_t cliLineFollowingController_setGain(uint8_t argNumber, 
                                                char* args[]);

#define LINE_FOLLOWING_CONTROLLER_COMMANDS                                                                                                    \
    {cliLineFollowingController_getKp,    "line-follow-get-thresh",  "<periph>",          "get line follower threshold",   0, 0}, \
    {cliLineFollowingController_setKp,    "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   1, 1}, \
    {cliLineFollowingController_getKd,    "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   0, 0}, \
    {cliLineFollowingController_setKd,    "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   1, 1}, \
    {cliLineFollowingController_getKi,    "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   0, 0}, \
    {cliLineFollowingController_setKi,    "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   1, 1}, \
    {cliLineFollowingController_setGain,  "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   0, 0}, \
    {cliLineFollowingController_setGain,  "line-follow-set-thresh",  "<periph> <thresh>", "set line follower threshold",   1, 1},
#endif // CLI_LINE_FOLLOWING_CONTROLLER