/*
 * lvr_relay.c
 *
 *  Created on: 24 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_relay.h"
#include "lvr_ble_api.h"
#include "lvr_gpio.h"

static uint8_t cnt;

void RELLVR_GetRelaySig(void)
{
	volatile char relayAttr = '0';
	if (cnt % 2)
	{
		relayAttr = (char) GetAttr(DOOR_LOCK_SERVICE, LS_RELAY_CHARAC);
	}

	if (relayAttr == 'O')
	{
		GPIOLVR_On(GPIO_8);
		DBG("H");
		SetAttr(DOOR_LOCK_SERVICE, LS_RELAY_CHARAC, '0');
	}
	else
	{
		GPIOLVR_Off(GPIO_8);
	}
	cnt++;
}
