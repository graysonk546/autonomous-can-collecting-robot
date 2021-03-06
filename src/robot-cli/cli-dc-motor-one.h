
#ifndef CLI_DC_MOTOR_ONE
#define CLI_DC_MOTOR_ONE
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"
#include "utilities/util-vars.h"
#include "cli-dc-motor-one.h"

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

cli_status_t cliDcMotorOne_init(uint8_t argNumber, char* args[]);

cli_status_t cliDcMotorOne_run(uint8_t argNumber, char* args[]);

#define DC_MOTOR_ONE_COMMANDS                                                                     \
    {cliDcMotorOne_init, "dc-one-init", "<periph>",         "init the 1D dc-motor periph", 1, 1},\
    {cliDcMotorOne_run,  "dc-one-run",  "<periph> <speed>", "run the 1D dc motor",         2, 2},
#endif // CLI_DC_MOTOR_ONE