
/*******************************************************************************
*                               Standard Libraries
*******************************************************************************/

#include <Arduino.h>
#include <HardwareTimer.h>

/*******************************************************************************
*                               Header Files
*******************************************************************************/

#include "sonar.h"

/*******************************************************************************
*                               Static Functions
*******************************************************************************/

/*******************************************************************************
*                               Constants
*******************************************************************************/

#define SONAR_PWM_TIMER     TIM3
#define SONAR_TIMER_CHANNEL 4
#define SONAR_PWM_FREQ      100  // 16Hz ~ 60ms PWM period (recomended)
#define SONAR_PWM_DUTY      3    // 3% duty cycle ~ 2ms pulse
#define SONAR_TRIG_PIN      PB1

/*******************************************************************************
*                               Structures
*******************************************************************************/

/*******************************************************************************
*                               Variables
*******************************************************************************/

static HardwareTimer* pwmTimer;

/*******************************************************************************
*                               Functions
*******************************************************************************/

robot_status_t sonar_init()
{
    // Initializing PWM (replaces analogWrite)
    pwmTimer = new HardwareTimer(SONAR_PWM_TIMER);
    pwmTimer->setPWM(SONAR_TIMER_CHANNEL, SONAR_TRIG_PIN, SONAR_PWM_FREQ, 
                     SONAR_PWM_DUTY);
    return ROBOT_OK;
}

robot_status_t sonar_deInit()
{
    digitalWrite(SONAR_TRIG_PIN, LOW);
    return ROBOT_OK;
}