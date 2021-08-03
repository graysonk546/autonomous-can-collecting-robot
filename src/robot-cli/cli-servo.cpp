/*******************************************************************************
*                               Standard Includes
*******************************************************************************/

/*******************************************************************************
*                               Header File Includes
*******************************************************************************/

#include "cli-servo.h"
#include "robot-core/servo.h"
#include "robot-core/command.h"
#include "utilities/util-vars.h"
#include "Servo.h"

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

static Servo myServo;

cli_status_t cliServo_init(uint8_t argNumber, char* args[])
{
    myServo.attach(PA0);
    // servo_motor_id_t servo_id = (servo_motor_id_t) strtol((const char*) args[0],
    //                                                       NULL, 0);

    // if (servo_id != HOPPER_ROTATION_SERVO && servo_id != HOPPER_LOADING_SERVO)
    // {
    //      Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
    //                  " servo\"}" CMD_EOL_STR));
    //     return COMMAND_OK;
    // }

    // servo_motor_t* servo = servo_get(servo_id);

    // if (servo_init(servo) == ROBOT_OK)
    // {
    //     Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));   
    // }
    // else
    // {
    //     Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"servo init"
    //                  " failed\"}" CMD_EOL_STR));
    // }
    return COMMAND_OK;
}

cli_status_t cliServo_rotate(uint8_t argNumber, char* args[])
{
    // int pos = 0;
    // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    //     // in steps of 1 degree
    //     myServo.write(pos);              // tell servo to go to position in variable 'pos'
    //     delay(10);
    //     Serial.println("1st for-loop");                       // waits 15ms for the servo to reach the position
    // }
    // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //     myServo.write(pos);              // tell servo to go to position in variable 'pos'
    //     delay(10);                       // waits 15ms for the servo to reach the position
    //     Serial.println("2nd for-loop");
    // }
    // Serial.println("Finished rotate...");

    // servo_motor_id_t servo_id = (servo_motor_id_t) strtol((const char*) args[0],
    //                                                       NULL, 0);
    int angle = (int) strtol((const char*) args[1], NULL, 0);

    myServo.write(angle);
    Serial.print("Angle: ");
    Serial.println(angle);

    // if (servo_id != HOPPER_ROTATION_SERVO && servo_id != HOPPER_LOADING_SERVO)
    // {
    //      Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
    //                   " reflectance sensor\"}" CMD_EOL_STR));
    //     return COMMAND_OK;
    // }
    // servo_motor_t* servo = servo_get(servo_id);

    // if (angle > MAX_ANGLE || angle < MIN_ANGLE)
    // {
    //     Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": invalid"
    //                  " angle\"}" CMD_EOL_STR));
    //     return COMMAND_OK;
    // }
    // if (servo_rotate(servo, angle) == ROBOT_OK)
    // {
    //     Serial.print(F(CMD_JSON "{\"status\": \"success\"}" CMD_EOL_STR));
    // }
    // else
    // {
    //      Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": "
    //                   "\"servo rotate failed\"}" CMD_EOL_STR));
    // }
    return COMMAND_OK;
}

cli_status_t cliServo_getInitAngle(uint8_t argNumber, char* args[])
{
    servo_motor_id_t servo_id = (servo_motor_id_t) strtol((const char*) args[0],
                                                          NULL, 0);
    if (servo_id != HOPPER_ROTATION_SERVO)
    {
         Serial.print(F(CMD_JSON "{\"status\": \"error\", \"data\": \"invalid"
                      " servo\"}" CMD_EOL_STR));
        return COMMAND_OK;
    }
    servo_motor_t* servo = servo_get(servo_id);
    return COMMAND_OK;
}

cli_status_t cliServo_setInitAngle(uint8_t argNumber, char* args[])
{
    return COMMAND_OK;
}