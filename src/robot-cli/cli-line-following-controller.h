#ifndef CLI_LINE_FOLLOWING_CONTROLLER
#define CLI_LINE_FOLLOWING_CONTROLLER
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "robot-core/command.h"
#include "utilities/util-vars.h"
#include "robot-control/line-following-controller.h"

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

cli_status_t cliLineFollowingController_getErr(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setTarg(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getTarg(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setMax(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getMax(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setMin(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getMin(uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_getDelocalizedReflectanceThreshold(
    uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setDelocalizedReflectanceThreshold(
    uint8_t argNumber, char* args[]);

cli_status_t cliLineFollowingController_setPreviousSpinOffset(uint8_t argNumber,
                                                              char* args[]);

cli_status_t cliLineFollowingController_getPreviousSpinOffset(uint8_t argNumber,
                                                              char* args[]);

cli_status_t cliLineFollowingController_setDelocalizedErrorMagnitude(uint8_t
    argNumber, char* args[]);

cli_status_t cliLineFollowingController_getDelocalizedErrorMagnitude(uint8_t
    argNumber, char* args[]);

cli_status_t cliLineFollowingController_poll(uint8_t argNumber, char* args[]);

#define LINE_FOLLOWING_CONTROLLER_COMMANDS                                                                                                    \
    {cliLineFollowingController_getKp,                               "get-kp",                           "",          "get kp",                                 0, 0}, \
    {cliLineFollowingController_setKp,                               "set-kp",                           "<kp>",      "set kp",                                 1, 1}, \
    {cliLineFollowingController_getKd,                               "get-kd",                           "",          "get kd",                                 0, 0}, \
    {cliLineFollowingController_setKd,                               "set-kd",                           "<kd>",      "set kd",                                 1, 1}, \
    {cliLineFollowingController_getErr,                              "get-error",                        "",          "get error",                              1, 1}, \
    {cliLineFollowingController_getTarg,                             "get-targ-speed",                   "",          "get target",                             0, 0}, \
    {cliLineFollowingController_setTarg,                             "set-targ-speed",                   "<speed>",   "set target",                             1, 1}, \
    {cliLineFollowingController_getMax,                              "get-max-speed",                    "",          "get max",                                0, 0}, \
    {cliLineFollowingController_setMax,                              "set-max-speed",                    "<speed>",   "set max",                                1, 1}, \
    {cliLineFollowingController_getMin,                              "get-min-speed",                    "",          "set min",                                0, 0}, \
    {cliLineFollowingController_setMin,                              "set-min-speed",                    "<speed>",   "set min",                                1, 1}, \
    {cliLineFollowingController_getDelocalizedReflectanceThreshold,  "get-delocalized-ref-thresh",       "",          "get delocalized reflectance threshold",  0, 0}, \
    {cliLineFollowingController_setDelocalizedReflectanceThreshold,  "set-delocalized-ref-thresh",       "<thresh>",  "set delocalized reflectance threshold",  1, 1}, \
    {cliLineFollowingController_getPreviousSpinOffset,               "get-previous-spin-offset",         "",          "get previous spin offset",               0, 0}, \
    {cliLineFollowingController_setPreviousSpinOffset,               "set-previous-spin-offset",         "<offset>",  "set previous spin offset",               1, 1}, \
    {cliLineFollowingController_getDelocalizedErrorMagnitude,        "get-delocalized-error-mag",        "",          "get delocalized error magnitude",        0, 0}, \
    {cliLineFollowingController_setDelocalizedErrorMagnitude,        "set-delocalized-error-mag",        "<mag>",     "set delocalized error magnitude",        1, 1}, \
    {cliLineFollowingController_poll,                                "poll-line-following-controller",   "",          "poll line following controller",         0, 0},

#endif // CLI_LINE_FOLLOWING_CONTROLLER
