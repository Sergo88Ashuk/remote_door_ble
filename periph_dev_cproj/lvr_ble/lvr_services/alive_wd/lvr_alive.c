/*
 * alive.c
 *
 *  Created on: 22 дек. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_alive.h"
#include "lvr_ble_api.h"

#define MAX_SILENCE_CYCLE	(8)

static uint8_t silenceCnt;
static uint8_t wd;

bool ALV_GetStatus(void)
{
	bool liveStat = true;

	if (wd == GetAttr(DOOR_HEALTH_SERVICE, HS_ALIVE_WD_CHARAC))
		{silenceCnt++;}

	liveStat = (silenceCnt < MAX_SILENCE_CYCLE) ? (true) : (false);

	return liveStat;
}

void ALV_Reset(void)
{
	silenceCnt = 0;
	wd = GetAttr(DOOR_HEALTH_SERVICE, HS_ALIVE_WD_CHARAC);
}
