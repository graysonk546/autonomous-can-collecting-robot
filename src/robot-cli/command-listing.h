
#ifndef COMMAND_LISTING
#define COMMAND_LISTING

/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "robot-core/command.h"
#include "cli-command.h"
#include "cli-dc-motor.h"
#include "cli-dc-motor-one.h"
#include "cli-dc-motor-two.h"
#include "cli-line-follower.h"
#include "cli-line-following-controller.h"
#include "cli-reflectance.h"
#include "cli-sonar.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define LIST_TERMINATOR "END_OF_LIST"

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables 
*******************************************************************************/

static const command_t commandArr[] = {
    COMMAND_COMMANDS
    DC_MOTOR_COMMANDS
    DC_MOTOR_ONE_COMMANDS
    DC_MOTOR_TWO_COMMANDS
    LINE_FOLLOWER_COMMANDS
    LINE_FOLLOWING_CONTROLLER_COMMANDS
    REFLECTANCE_COMMANDS
    SONAR_COMMANDS
    {NULL, LIST_TERMINATOR, NULL, NULL, 0, 0}
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

#endif // COMMAND_LISTING