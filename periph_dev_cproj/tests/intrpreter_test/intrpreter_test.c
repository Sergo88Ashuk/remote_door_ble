/*
 * intrpreter_test.c
 *
 *  Created on: 2 но€б. 2018 г.
 *      Author: lvr_laptop
 */

#include "lvr_gpio.h"
#include "intrpreter_test.h"

static char funcBox[128];
static char NOP[] = {0xC0, 0x46};
static char ISB[] = {0xBF, 0xF3, 0x6F, 0x8F};
static char DMB[] = {0xBF, 0xF3, 0x5F, 0x8F};

__attribute__((used))
__attribute__((noinline))
__attribute__((section("bar")))
void BAR(void)
{
	__ISB();
	__DMB();
}

__attribute__((used))
__attribute__((noinline))
__attribute__((section("call2a")))
void CALL2A(char* funcAddr, char* kvantAddr, uint32_t arg0, uint32_t arg1)
{
	typedef void (*fcn)(char*, uint32_t, uint32_t);
	fcn func = (fcn) funcAddr;
	func(kvantAddr, arg0, arg1);
}

__attribute__((used))
__attribute__((noinline))
__attribute__((section("call1a")))
void CALL1A(char* funcAddr, uint32_t arg0)
{
	typedef void (*fcn)(uint32_t);
	fcn func = (fcn) funcAddr;
	func(arg0);
}

__attribute__((used))
__attribute__((noinline))
__attribute__((section("ret")))
uint32_t RET(char* funcAddr)
{
	typedef void (*fcn)(void);
	fcn func = (fcn) funcAddr;
	return (uint32_t) func;
}

//typedef void (*fcn)(uint32_t);
//fcn func = (fcn) funcAddr;
//func(arg0);

__attribute__((used))
__attribute__((noinline))
__attribute__((section("kvant")))
void KVANT(uint32_t evalFunc, uint32_t arg0, uint32_t arg1)
{
	typedef uint32_t (*fcn)(uint32_t, uint32_t);
	fcn func = (fcn) evalFunc;
	if(func(arg0, arg1))
	{
		GPIOLVR_OUT = (uint32_t) (1U << 8U);
	}
	else
	{
		GPIOLVR_OUT = (uint32_t) (0U);
	}
}

__attribute__((used))
__attribute__((noinline))
__attribute__((section("eq")))
uint32_t EQ(uint32_t val0, uint32_t val1)
{
	return  (val0 == val1);
}

extern unsigned char __start_eq[];
extern unsigned char __stop_eq[];
extern unsigned char __start_kvant[];
extern unsigned char __stop_kvant[];
extern unsigned char __start_call2a[];
extern unsigned char __stop_call2a[];
extern unsigned char __start_call1a[];
extern unsigned char __stop_call1a[];
extern unsigned char __start_ret[];
extern unsigned char __stop_ret[];
extern unsigned char __start_bar[];
extern unsigned char __stop_bar[];

uint32_t GetFunc(char* codeBuf, uint32_t* argBuf)
{
	if (codeBuf == NULL)
	{
		volatile uint32_t i = EQ(0, 0);i++;
		volatile uint32_t j = RET(0);j++;
		KVANT(0, 0, 0);
		CALL2A(0, 0, 0, 0);
		CALL1A(0, 0);
		BAR();
	}

	volatile uint32_t eqSize = (uint32_t) (__stop_eq - __start_eq);
	volatile uint32_t kvantSize = (uint32_t) (__stop_kvant - __start_kvant);
	volatile uint32_t call2aSize = (uint32_t) (__stop_call2a - __start_call2a);
	volatile uint32_t call1aSize = (uint32_t) (__stop_call1a - __start_call1a);
	volatile uint32_t retSize = (uint32_t) (__stop_ret - __start_ret);
	volatile uint32_t barSize = (uint32_t) (__stop_bar - __start_bar);
	volatile uint32_t nopSize = sizeof(NOP);
	volatile uint32_t isbSize = sizeof(ISB);
	volatile uint32_t dmbSize = sizeof(DMB);

	memset(funcBox, 0, 128);
	memset(codeBuf, 0, 128);

	uint16_t i = 0;

	memcpy(&funcBox[i], __start_kvant, kvantSize);
	memcpy(&codeBuf[i], __start_kvant, kvantSize);
	i += kvantSize;

	argBuf[0] = (uint32_t) &codeBuf[i];
	memcpy(&funcBox[i], __start_eq, eqSize);
	memcpy(&codeBuf[i], __start_eq, eqSize);
	i += eqSize;
//	for (uint16_t i = 0; i < (eqSize + kvantSize); i++)
//	{
//		DBG("\r\n addr[0x%02X]; val[0x%02X]",(unsigned int) &codeBuf[i], (unsigned int) codeBuf[i]);
//	}
//
//	for (uint8_t i = 0; i < 2; i++)
//	{
//		DBG("\r\narg[%d] = [0x%02X]", i, (unsigned int) argBuf[i]);
//	}
//
//	DBG("\r\nsize = [0x%02X]", (unsigned int) (eqSize + kvantSize));
	return (barSize + eqSize + kvantSize + dmbSize + isbSize +
			call2aSize + retSize + call1aSize + nopSize);
}
