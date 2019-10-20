/*
 * lvr_batt.c
 *
 *  Created on: 24 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_batt.h"
#include "lvr_ble_api.h"
#include "lvr_adc.h"

void BATTLVR_SetLevelCharac(void)
{
	uint32_t adcVal = ADCLVR_Get();
	SetAttr(DOOR_HEALTH_SERVICE, HS_BATT_CHARAC, (adcVal >> 2));
//	DBG("\r\nadc = [0x%02X]", (unsigned int) adcVal);

}
