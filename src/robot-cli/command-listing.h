
#ifndef RECEPTOR_COMMANDS
#define RECEPTOR_COMMANDS

#include "cli-command.h"
#include "cli-accelerometer.h"

#define LIST_TERMINATOR "END_OF_LIST"

static const command_t commandArr[] = {
    COMMAND_COMMANDS
    ACCELEROMETER_COMMANDS
    {NULL, "END_OF_LIST", NULL, NULL, NULL, NULL}
};

#endif // RECEPTOR_COMMANDS