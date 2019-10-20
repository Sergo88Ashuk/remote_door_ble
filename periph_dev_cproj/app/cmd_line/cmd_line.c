/*
 * debug_cmds.c
 *
 *  Created on: 15 сент. 2018 г.
 *      Author: lvr_laptop
 */

#include "../global_defs.h"
#include "../terminal/terminal.h"
#include "../debug.h"
#include "../intrpreter_test/intrpreter_test.h"
#include "lvr_ble_api.h"
#include "lvr_gpio.h"
#include "lvr_rtc.h"
#include "lvr_tim.h"
#include "lvr_adc.h"

#define GetArgDec(n, arg) 	 {if (!TERM_GetArgDec(n, &(arg))){cmdResult = TERM_ArgErr;}}
#define GetArgStr(n, arg)	 {if (!TERM_GetArgStr(n, (arg))){cmdResult = TERM_ArgErr;}}

char 	 funcCode[128];
uint32_t funcArgs[8];

typedef void (*fcni)(uint32_t, uint32_t, uint32_t);
fcni func ;

static Terminal_cmd_return_s _Test(void);       // Terminal test
static Terminal_cmd_return_s _TestRtc(void);
static Terminal_cmd_return_s _TestTim(void);
static Terminal_cmd_return_s _TestAdc(void);

// Following functions must be relying
// on new module server_test instead of adv_test
static Terminal_cmd_return_s _GetAttr(void);
static Terminal_cmd_return_s _SetAttr(void);
static Terminal_cmd_return_s _ConfigBle(void);
static Terminal_cmd_return_s _AddServ(void);		// add service
static Terminal_cmd_return_s _AddCharac(void);		// add characteristic to service
static Terminal_cmd_return_s _SwitchSoftDev(void);	// enable/disable softdevice
static Terminal_cmd_return_s _SwitchAdv(void);		// start/stop advertising
static Terminal_cmd_return_s _DumpServerInfo(void);	// dump info about server device:
													// attr table|connection status|server params

// Functioms for interpreter tests
static Terminal_cmd_return_s _GpioOn(void);
static Terminal_cmd_return_s _GpioOff(void);
static Terminal_cmd_return_s _FuncBuf(void);

void DBGCMD_Init(void)
{
		TERM_AddCmd("test",       _Test,    2,	"very first cmd for test purpose");
		TERM_AddCmd("testrtc",    _TestRtc,    0,	"rtc test");
		TERM_AddCmd("testtim",    _TestTim,    0,	"timer test");
		TERM_AddCmd("testadc",    _TestAdc,    0,	"adc test");

	/*************************************************************************************/

		TERM_AddCmd("swsd",      _SwitchSoftDev,  1, "switch soft device on/off; arg[1] - on or off");
		TERM_AddCmd("confble",   _ConfigBle,      2, "config ble stack parameters; "
												 "arg[1] - state on or off"
												 "arg[2] - use default or user defined service params"); // NOTE: hardcoded to default
		TERM_AddCmd("addserv",   _AddServ,        2, "adding service; "
			 	 	 	 	 	 	 	 	 	 "arg[1] - service's number"
			 	 	 	 	 	 	 	 	 	 "arg[2] - use default or user defined service params"); // NOTE: hardcoded to default
		TERM_AddCmd("addcharac", _AddCharac,      3, "adding characteristic; "
												 "arg[1] - service's number"
												 "arg[2] - characteristic's number"
												 "arg[3] - use default or user defined characteristics params");
		TERM_AddCmd("swadv",     _SwitchAdv,      1, "switch advertising on/off; arg[1] - on or off");
/*DONE*/TERM_AddCmd("getattr",   _GetAttr,        2, "get value of attribute; "
												 "arg[1] - characteristic's number"
												 "arg[2] - service's number");
/*DONE*/TERM_AddCmd("setattr",   _SetAttr,        3, "set value of attribute; "
												 "arg[1] - value"
												 "arg[2] - characteristic's number"
												 "arg[3] - service's number");
		TERM_AddCmd("dump",      _DumpServerInfo, 2, "dump requested data; "
													 "arg[1] - type of dump"
													 "arg[2] - verbose level");
	/*************************************************************************************/
		TERM_AddCmd("gpioon",  _GpioOn, 0, "gpio on");
		TERM_AddCmd("gpiooff", _GpioOff, 0, "gpio off");
		TERM_AddCmd("fdump",   _FuncBuf, 2, "get function");
}

static Terminal_cmd_return_s _TestAdc(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t adcVal = ADCLVR_Get();
	DBG("\r\nadc = [0x%02X]", (unsigned int) adcVal);

	return cmdResult;
}

static Terminal_cmd_return_s _TestTim(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;
	TIM1LVR_Init();
	return cmdResult;
}

static Terminal_cmd_return_s _TestRtc(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;
	RTC1LVR_Init();
	return cmdResult;
}

static Terminal_cmd_return_s _FuncBuf(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t arg0, arg1;
	GetArgDec(0, arg0);
	GetArgDec(1, arg1);

	GetFunc(funcCode, funcArgs);
	func = (fcni) ((uint32_t)funcCode | 1);
	func((funcArgs[0] | 1 ), arg0, arg1);
	DBG("\r\n[0x%02X] [0x%02X]", (unsigned int) ((uint32_t)funcCode | 1),
								(unsigned int) (funcArgs[0] | 1 ));

	return cmdResult;
}

static Terminal_cmd_return_s _GpioOn(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

//	typedef void (*fcn)(uint32_t);
//	fcn func;
//	GetFunc(funcBuf);
//	func = (fcn) funcBuf;
//	func((uint32_t) (1U << 8U));

	return cmdResult;
}

static Terminal_cmd_return_s _GpioOff(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

//	typedef void (*fcn)(uint32_t);
//	fcn func;
//	GetFunc(funcBuf);
//	func = (fcn) funcBuf;
//	func((uint32_t) 0);

	return cmdResult;
}

static Terminal_cmd_return_s _AddServ(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t defaultParams, servName;
	GetArgDec(0, servName);
	GetArgDec(1, defaultParams);
	DBG("\r\n[0x%02X] [0x%02X]", (unsigned int) servName, (unsigned int) defaultParams);
	StartService(servName, (bool) defaultParams);

	return cmdResult;
}

static Terminal_cmd_return_s _ConfigBle(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t gattsSize, state;
	GetArgDec(0, state);
	GetArgDec(1, gattsSize);
	DBG("\r\n[0x%02X] [0x%02X]", (unsigned int) state, (unsigned int) gattsSize);
	StartBleStack((bool) state, (uint16_t) gattsSize);

	return cmdResult;
}

static Terminal_cmd_return_s _AddCharac(void)
{
	// add characteristic to service
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t defaultParams, servName, characName;
	GetArgDec(0, servName);
	GetArgDec(1, characName);
	GetArgDec(2, defaultParams);
//	DBG("\r\n[0x%02X] [0x%02X], [0x%02X]", (unsigned int) servName, (unsigned int) characName, (unsigned int) defaultParams);
	StartCharact((uint8_t) servName, (uint8_t) characName,
									  (bool) defaultParams);

	return cmdResult;
}

static Terminal_cmd_return_s _SwitchSoftDev(void)
{
	// enable/disable softdevice
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t sdState;
	GetArgDec(0, sdState);
	DBG("\r\n[0x%02X]", (unsigned int) sdState);
	StartSoftDevice((bool) sdState);

	return cmdResult;
}

static Terminal_cmd_return_s _SwitchAdv(void)
{
	// start/stop advertising
	Terminal_cmd_return_s cmdResult = TERM_OK;

	uint32_t advState;
	GetArgDec(0, advState);
	StartAdvert((bool) advState);

	return cmdResult;
}

static Terminal_cmd_return_s _DumpServerInfo(void)
{
	// dump info about server device:
	// attr table|connection status|server params
	Terminal_cmd_return_s cmdResult = TERM_OK;

	char dumpArg[MAX_ARGUMENT_LENGTH];
	uint32_t verbLvl;
	GetArgStr(0, dumpArg);
	GetArgDec(1, verbLvl);

	// parse what type of dump is requested
	// call corresponding function

	return cmdResult;
}

static Terminal_cmd_return_s _GetAttr(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;
	uint32_t charac, serv;
	GetArgDec(0, charac);
	GetArgDec(1, serv);

	volatile uint8_t val = GetAttr(serv, charac);
	DBG("\r\nattr val: 0x%02X", val);

	return cmdResult;
}

static Terminal_cmd_return_s _SetAttr(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;
	uint32_t attrVal = 0;
	uint32_t serv, charac;
	GetArgDec(0, attrVal);
	GetArgDec(1, charac);
	GetArgDec(2, serv);

	SetAttr(serv, charac, attrVal);

	return cmdResult;
}

static Terminal_cmd_return_s _Test(void)
{
	Terminal_cmd_return_s cmdResult = TERM_OK;

	char arg0[MAX_ARGUMENT_LENGTH];
	char arg1[MAX_ARGUMENT_LENGTH];
	DBG("\r\n[0x%02X] [0x%02X]", (unsigned int) arg0, (unsigned int) arg1);
	GetArgStr(0, arg0);
	GetArgStr(1, arg1);
	DBG("\r\n[0x%02X] [0x%02X]", (unsigned int) arg0, (unsigned int) arg1);
	DBG("\r\n[%s] [%s]", arg0, arg1);

	return cmdResult;
}
