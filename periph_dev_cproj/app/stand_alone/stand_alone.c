/*
 * stand_alone.c
 *
 *  Created on: 27 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "stand_alone.h"
#include "lvr_evth.h"
#include "lvr_batt.h"
#include "lvr_gercon.h"
#include "lvr_relay.h"
#include "lvr_alive.h"
#include "lvr_tim.h"
#include "lvr_ble_api.h"

static volatile uint8_t cnt;
static volatile bool connected;

typedef enum
{
	STALN_Advert = 0,
	STALN_Connected,
	STALN_Disconnected,
}STALN_States;
STALN_States state;

char* stateStr[] = {"STALN_ADVERT", "STALN_CONN", "STALN_DISC"};

static void _AdvertState(void);
static void _ConnState(void);
static void _DiscState(void);

void ConStateCb(bool state);

void (*StateTable[])() =
{
	_AdvertState, _ConnState, _DiscState
};

void STALN_App(void)
{
	TIM1LVR_Init();
	BLELVR_InitServer();
	EVTH_RegCallb(ConStateCb);

	state = STALN_Advert;
	while (true)
	{
		DBG("\r\n<<%s>>", stateStr[state]);
		StateTable[state]();
	}
}

static void _AdvertState(void)
{
	connected = false;
	StartAdvert(true);

	while (!connected) {};
	StartAdvert(false);

	state = STALN_Connected;
}

static void _ConnState(void)
{
	cnt = 0;
//	ALV_Reset();

	while (/*ALV_GetStatus() &&*/ connected)
	{
		if (cnt == 4)
		{
			BATTLVR_SetLevelCharac();
			GRCLVR_SetStateCharac();
			RELLVR_GetRelaySig();
			cnt = 0;
		}
	}

	state = STALN_Disconnected;
}
static void _DiscState(void)
{
	// todo: implement security stuff i.e. lock the door, etc.
	state = STALN_Advert;
}

void TIMER1_IRQHandler(void)
{
	TIM1LVR_STOP = HIGH;
	TIM1LVR_COMPARE[0] = LOW;
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	TIM1LVR_CLEAR = HIGH;
	cnt++;
//	GPIOLVR_Toggle();
	TIM1LVR_START = HIGH;
}

void ConStateCb(bool state)
{
	DBG("\r\nCALLBACK state [%d]", (state) ? (1) : (0));
	connected = (state) ? (true) : (false);
}


