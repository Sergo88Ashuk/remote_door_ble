/*
 * lvr_uart.c
 *
 *  Created on: 12 сент. 2018 г.
 *      Author: lvr_laptop
 */

#include "../../lvrsoc_hw/lvr_uart/lvr_uart.h"

static bool firstTx;

void UARTLVR_Stop(void)
{
	UARTLVR_STOPTX  = HIGH;
	UARTLVR_STOPRX  = HIGH;
}

void UARTLVR_Start(void)
{
	UARTLVR_STARTTX = HIGH;
	UARTLVR_STARTRX = HIGH;
	firstTx = true;
}

void UARTLVR_Init(uint8_t rxPin, uint8_t txPin, uint32_t baud)
{
	UARTLVR_PSELTXD  = txPin;
	UARTLVR_PSELRXD  = rxPin;
	UARTLVR_BAUDRATE = baud;
	UARTLVR_ENABLE	 = ENABLE;
	UARTLVR_INTEN	 = (1 << TXDRDY_INT_BIT)
					 | (1 << RXDRDY_INT_BIT);
	UARTLVR_TXDRDY = LOW;
	UARTLVR_RXDRDY = LOW;
}

char UARTLVR_GetSym(void)
{
	while(!UARTLVR_RXDRDY){};
	return UARTLVR_RXD;
}

void UARTLVR_PutSym(char sym)
{
	if (firstTx)
	{
		UARTLVR_TXD = sym;
		firstTx = false;
	}
	else
	{
		while(!UARTLVR_TXDRDY){};
		UARTLVR_TXDRDY = LOW;
		UARTLVR_TXD = sym;
	}
}
