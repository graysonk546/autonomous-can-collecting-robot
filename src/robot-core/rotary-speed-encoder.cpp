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
    pinMode(encoder->pin, INPUT_PULLDOWN);
    encoder->lastInterruptTime = millis();
    attachInterrupt(digitalPinToInterrupt(encoder->pin), encoder->isr, RISING);
    encoder->initialized = true;
    return ROBOT_OK;
}

rotary_speed_encoder_t* rotarySpeedEncoder_get(rotary_speed_encoder_id_t id)
{
    return &rotarySpeedEncoderArr[id];
}

static void _rollerSpeedEncoder_ISR()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (digitalRead(PIN_ROLLER_MOTOR_ENCODER) != HIGH)
        {
            return;
        }

    }
    rotarySpeedEncoderArr[ROLLER_SPEED_ENCODER].lastInterruptTime = millis();
}
