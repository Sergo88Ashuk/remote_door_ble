/*
 * lvr_gercon.c
 *
 *  Created on: 24 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_gercon.h"
#include "lvr_ble_api.h"
#include "lvr_gpio.h"

void GRCLVR_SetStateCharac(void)
{
	volatile bool grcState = GPIOLVR_Get(GPIO_10);
#if 1
	SetAttr(DOOR_LOCK_SERVICE, LS_GERCON_CHARAC, ((grcState) ? (0x00) : (0xCC)));
#else
	DBG("\r\n pin10 [0x%02X]", (unsigned int) grcState);
	if(grcState)
	{
		SetAttr(DOOR_LOCK_SERVICE, LS_GERCON_CHARAC, 0x00);
		GPIOLVR_On(GPIO_8);
	}
	else
	{
		SetAttr(DOOR_LOCK_SERVICE, LS_GERCON_CHARAC, 0xCC);
		GPIOLVR_Off(GPIO_8);
	}

#endif
}

