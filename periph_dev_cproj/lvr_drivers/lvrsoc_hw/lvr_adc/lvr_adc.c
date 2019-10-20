/*
 * lvr_adc.c
 *
 *  Created on: 24 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_adc.h"

void ADCLVR_Init(void)
{
	ADCLVR_CONFIG &= ~(ADCLVR_RES_MASK
						<< ADCLVR_RES_OFFSET);
	ADCLVR_CONFIG |= (RES_10B << ADCLVR_RES_OFFSET);


	ADCLVR_CONFIG &= ~(ADCLVR_INPSEL_MASK
						<< ADCLVR_INPSEL_OFFSET);
	ADCLVR_CONFIG |= (ANIN_1_3_PRSCL << ADCLVR_INPSEL_OFFSET);


	ADCLVR_CONFIG &= ~(ADCLVR_PINSEL_MASK
						<< ADCLVR_PINSEL_OFFSET);
	ADCLVR_CONFIG |= (ANIN7 << ADCLVR_PINSEL_OFFSET);
}

void ADCLVR_Start(void)
{

}

uint32_t ADCLVR_Get(void)
{
	ADCLVR_ENABLE = HIGH;
	ADCLVR_START = HIGH;
	while (ADCLVR_BUSY){};
	return (uint32_t) ADCLVR_RESULT;
}

