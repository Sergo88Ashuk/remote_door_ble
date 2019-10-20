/*
 * terminal.h
 *
 *  Created on: 11 θών. 2018 γ.
 *      Author: lvr_laptop
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "global_defs.h"
#include "terminal_conf.h"
#include "../debug.h"

#define TERM_PF(x) 		{{UARTLVR_PutSym('\r');}\
						 {UARTLVR_PutSym('\n');}\
						 {DBG(x);}}


typedef enum
{
	TERM_OK = 0,
	TERM_ExecErr,
	TERM_ArgErr,
	TERM_CmdCanceled,
	TERM_BadCmd
}Terminal_cmd_return_s;

/*
typedef enum
{

}Terminal_obj_status_s;
*/

typedef struct
{
	char argv[MAX_ARGUMENTS_QTY][MAX_ARGUMENT_LENGTH];
	uint8_t argc;
}Terminal_arg_s;

typedef Terminal_cmd_return_s (*fcn)(void);

typedef struct
{
	const char* name;
	const char* info;
	uint8_t argsNum;
	fcn ExecCode;
}Terminal_cmd_s;

typedef struct
{
	uint8_t execIndex;
	volatile bool execFlag;
	volatile bool cancelFlag;
	Terminal_cmd_return_s cmdReturn;
	uint16_t termPos;
	uint8_t cmdCount;
	Terminal_cmd_s termCmd[NUMBER_OF_COMMANDS];
	char inputStr[MAX_INPUT_STR_LENGTH];
}Terminal_s;

void			TERM_Init(void);
Terminal_s* 	TERM_GetTerminal(void);
Terminal_arg_s*	TERM_GetArgs(void);
bool 			TERM_PutChar(char sym);
bool			TERM_ExecCmd(void);
bool			TERM_IsCanceled(void);
bool			TERM_GetArgDec(uint8_t argNum, uint32_t* val);
bool			TERM_GetArgHex(uint8_t argNum, uint32_t* val);
bool 			TERM_GetArgStr(uint8_t argNum, char* str);
bool 			TERM_AddCmd(const char* strName, fcn execCode, uint8_t argNum, const char* strInfo);

#endif /* TERMINAL_TERMINAL_H_ */
