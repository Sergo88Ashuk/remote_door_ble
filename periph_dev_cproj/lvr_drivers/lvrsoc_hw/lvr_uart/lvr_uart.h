/*
 * lvr_uart.h
 *
 *  Created on: 12 сент. 2018 г.
 *      Author: lvr_laptop
 */

#ifndef BARE_DRIVERS_CPROJ_LVR_UART_H_
#define BARE_DRIVERS_CPROJ_LVR_UART_H_

#include "global_defs.h"

#define HIGH	(1)
#define LOW		(0)

#define UARTLVR_BA					(0x40002000)

#define UARTLVR_STARTRX_OFFSET		(0x00)
#define UARTLVR_STOPRX_OFFSET		(0x04)
#define UARTLVR_STARTTX_OFFSET		(0x08)
#define UARTLVR_STOPTX_OFFSET		(0x0C)
#define UARTLVR_SUSPEND_OFFSET		(0x1C)
#define UARTLVR_STARTRX				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_STARTRX_OFFSET)))
#define UARTLVR_STOPRX				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_STOPRX_OFFSET)))
#define UARTLVR_STARTTX				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_STARTTX_OFFSET)))
#define UARTLVR_STOPTX				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_STOPTX_OFFSET)))
#define UARTLVR_SUSPEND				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_SUSPEND_OFFSET)))

#define UARTLVR_CTS_OFFSET			(0x100)
#define UARTLVR_NCTS_OFFSET			(0x104)
#define UARTLVR_RXDRDY_OFFSET		(0x108)
#define UARTLVR_TXDRDY_OFFSET		(0x11C)
#define UARTLVR_ERROR_OFFSET		(0x124)
#define UARTLVR_RXTO_OFFSET			(0x144)
#define UARTLVR_CTS					(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_CTS_OFFSET)))
#define UARTLVR_NCTS				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_NCTS_OFFSET)))
#define UARTLVR_RXDRDY				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_RXDRDY_OFFSET)))
#define UARTLVR_TXDRDY				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_TXDRDY_OFFSET)))
#define UARTLVR_ERROR				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_ERROR_OFFSET)))
#define UARTLVR_RXTO				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_RXTO_OFFSET)))

#define UARTLVR_INTEN_OFFSET		(0x300)
#define UARTLVR_INTENSET_OFFSET		(0x304)
#define UARTLVR_INTENCLR_OFFSET		(0x308)
#define UARTLVR_ERRORSRC_OFFSET		(0x480)
#define UARTLVR_ENABLE_OFFSET		(0x500)
#define UARTLVR_PSELRTS_OFFSET		(0x508)
#define UARTLVR_PSELTXD_OFFSET		(0x50C)
#define UARTLVR_PSELCTS_OFFSET		(0x510)
#define UARTLVR_PSELRXD_OFFSET		(0x514)
#define UARTLVR_RXD_OFFSET			(0x518)
#define UARTLVR_TXD_OFFSET			(0x51C)
#define UARTLVR_BAUDRATE_OFFSET		(0x524)
#define UARTLVR_CONFIG_OFFSET		(0x56C)
#define UARTLVR_INTEN				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_INTEN_OFFSET)))
#define UARTLVR_INTENSET			(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_INTENSET_OFFSET)))
#define UARTLVR_INTENCLR			(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_INTENCLR_OFFSET)))
#define UARTLVR_ERRORSRC			(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_ERRORSRC_OFFSET)))
#define UARTLVR_ENABLE				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_ENABLE_OFFSET)))
#define UARTLVR_PSELRTS				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_PSELRTS_OFFSET)))
#define UARTLVR_PSELTXD				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_PSELTXD_OFFSET)))
#define UARTLVR_PSELCTS				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_PSELCTS_OFFSET)))
#define UARTLVR_PSELRXD				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_PSELRXD_OFFSET)))
#define UARTLVR_RXD					(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_RXD_OFFSET)))
#define UARTLVR_TXD					(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_TXD_OFFSET)))
#define UARTLVR_BAUDRATE			(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_BAUDRATE_OFFSET)))
#define UARTLVR_CONFIG				(*((volatile uint32_t*)(UARTLVR_BA + UARTLVR_CONFIG_OFFSET)))

#define ENABLE	(0x04)
#define DISABLE	(0x00)

#define CTS_INT_BIT		(0)
#define NCTS_INT_BIT	(1)
#define RXDRDY_INT_BIT	(2)
#define TXDRDY_INT_BIT	(7)
#define ERROR_INT_BIT	(9)
#define RXTO_INT_BIT	(17)



void UARTLVR_PutSym(char sym);
char UARTLVR_GetSym(void);
void UARTLVR_Init(uint8_t rxPin, uint8_t txPin, uint32_t baud);
void UARTLVR_Start(void);
void UARTLVR_Stop(void);

#endif /* BARE_DRIVERS_CPROJ_LVR_UART_H_ */
