/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "utilities/robot-config.h"
#include "rotary-speed-encoder.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

static void _rollerSpeedEncoder_ISR();

/*******************************************************************************
*                               Constants
*******************************************************************************/

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static rotary_speed_encoder_t rotarySpeedEncoderArr[] =
{
    [ROLLER_SPEED_ENCODER] =
    {
        .pin               = PIN_ROLLER_MOTOR_ENCODER,
        .id                = ROLLER_SPEED_ENCODER,
        .isr               = &(_rollerSpeedEncoder_ISR),
        .lastInterruptTime = 0,
        .initialized       = false
    }
};

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t rotarySpeedEncoder_init(rotary_speed_encoder_t* encoder)
{
    pinMode(encoder->pin, INPUT);
    encoder->lastInterruptTime = millis();
    encoder->initialized = true;
    return ROBOT_OK;
}

rotary_speed_encoder_t* rotarySpeedEncoder_get(rotary_speed_encoder_id_t id)
{
    return &rotarySpeedEncoderArr[id];
}

static void _rollerSpeedEncoder_ISR()
{
    rotarySpeedEncoderArr[ROLLER_SPEED_ENCODER].lastInterruptTime = millis();
}
