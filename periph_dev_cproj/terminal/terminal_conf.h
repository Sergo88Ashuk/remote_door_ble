/*
 * terminal_conf.h
 *
 *  Created on: 11 θών. 2018 γ.
 *      Author: lvr_laptop
 */

#ifndef TERMINAL_TERMINAL_CONF_H_
#define TERMINAL_TERMINAL_CONF_H_

//#include "global_inc.h"
#include "../lvr_drivers/lvrsoc_hw/lvr_uart/lvr_uart.h"

#define NUMBER_OF_COMMANDS		(16)
#define MAX_ARGUMENTS_QTY		(16)
#define MAX_ARGUMENT_LENGTH		(16)
#define MAX_INPUT_STR_LENGTH	(272)

#define TERM_PORT	UART_3
#define GetChar		UARTLVR_GetSym
#define PutChar		UARTLVR_PutSym

#endif /* TERMINAL_TERMINAL_CONF_H_ */
