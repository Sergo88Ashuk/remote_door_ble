/*
 * cmd_line_start.c
 *
 *  Created on: 29 ����. 2018 �.
 *      Author: lvr_laptop
 */

#include "cmd_line.h"

void CMDL_Start(void)
{
	TERM_Init();
	DBGCMD_Init();

	while (true)
	{
		TERM_PutChar(UARTLVR_GetSym());
		TERM_ExecCmd();
	}
}
