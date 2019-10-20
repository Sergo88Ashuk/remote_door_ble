/*
 * lvr_gpio.c
 *
 *  Created on: 12 сент. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_gpio.h"

bool GPIOLVR_Get(uint8_t pinNum)
{
	return (GPIOLVR_IN & (1 << pinNum));
}

void GPIOLVR_Init(uint8_t pinNum, bool outPut) //todo: bool output looks bad in init funct from top
{
	if (outPut) {GPIOLVR_DIR |= (1U << pinNum);}
	else
	{
		GPIOLVR_DIR &= ~(1U << pinNum);
		GPIOLVR_CNF[pinNum] &= ~(1 << 1);
	}
}

void GPIOLVR_On(uint8_t pinNum)
{
	GPIOLVR_OUT |= (1U << pinNum);
}

void GPIOLVR_Off(uint8_t pinNum)
{
	GPIOLVR_OUT &= ~(1U << pinNum);
}

void GPIOLVR_Toggle(uint8_t pinNum)
{
	GPIOLVR_OUT ^= (1U << pinNum);
}
