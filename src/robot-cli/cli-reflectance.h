#ifndef CLI_REFLECTANCE
#define CLI_REFLECTANCE
/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-command.h"

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

cli_status_t cliReflectance_init(uint8_t argNumber, char* args[]);

cli_status_t cliReflectance_read(uint8_t argNumber, char* args[]);

#define REFLECTANCE_COMMANDS                                                               \
    {cliReflectance_init, "ref-init", "<periph>", "init the reflectance periph", 1, 1},    \
    {cliReflectance_read, "ref-read", "<periph>", "read a reflectance sensor value", 1, 1},
#endif // CLI_REFLECTANCE