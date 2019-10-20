/*
 * lvr_rtc.c
 *
 *  Created on: 20 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_rtc.h"
#include "lvr_gpio.h"

void RTC1LVR_Init(void)
{
	NVIC_SetPriority(RTC1_IRQn, 3);
	RTC1LVR_STOP |= 1;
	*((volatile uint32_t*) 0x40011144) = 100;
	NVIC_ClearPendingIRQ(RTC1_IRQn);
	NVIC_EnableIRQ(RTC1_IRQn);
	RTC1LVR_INTEN |= (1 << 17);
	RTC1LVR_START |= 1;

}

void RTC1LVR_Start(void)
{

}

void RTC1LVR_Stop(void)
{

}

void RTC1_IRQHandler(void)
{
	RTC1LVR_STOP |= 1;
	NVIC_ClearPendingIRQ(RTC1_IRQn);
	GPIOLVR_Toggle(GPIO_8);
	RTC1LVR_INTEN |= (1 << 17);
	RTC1LVR_START |= 1;

}
