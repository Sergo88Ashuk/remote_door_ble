/*
 * lvr_tim.c
 *
 *  Created on: 23 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_tim.h"
#include "lvr_gpio.h"

void TIM1LVR_Init(void)
{
	TIM1LVR_STOP = HIGH;
	TIM1LVR_CLEAR = HIGH;
	TIM1LVR_PRSCL = 7;
	TIM1LVR_MODE = LOW;
	TIM1LVR_CAPCOM = 31250;
	NVIC_SetPriority(TIMER1_IRQn, 3);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	NVIC_EnableIRQ(TIMER1_IRQn);
	TIM1LVR_INTENSET = (1 << CMP0_OFFSET);
	TIM1LVR_START = HIGH;
}

void TIM1LVR_Start(void)
{

}

void TIM1LVR_Stop(void)
{

}
