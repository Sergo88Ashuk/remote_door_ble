/*
 * terminal.c
 *
 *  Created on: 11 θών. 2018 γ.
 *      Author: lvr_laptop
 */

#include "terminal.h"

static Terminal_s 		term;
static Terminal_arg_s	inArgs;

static bool _IsValid(char sym);
static bool _AddToString(char sym);
static inline void _BackspaceSequence(void);
static inline void _EnterSequence(void);
static inline void _EscapeSequence(void);

static bool _ParseInputStr(char* str);
static bool _CmdSearch(char* str);
static Terminal_cmd_return_s _ExecCmd(void);
static bool _ResetTerm(void);
static bool _StringCmp(const char* str1, const char* str2);
static void _PrintArrows(void);

Terminal_s* TERM_GetTerminal(void)
{
	return &term;
}

Terminal_arg_s* TERM_GetArgs(void)
{
	return &inArgs;
}

bool TERM_PutChar(char sym)
{
	//check if the symbol is valid
	if (!_IsValid(sym))
	{
		return false;
	}
	//check if the symbol is special
	if (sym == 0x7F)
	{
		//backspace sequence
		_BackspaceSequence();
		return true;
	}
	if (sym == 0x0D)
	{
		//enter sequence
		_EnterSequence();
		return true;
	}
	if (sym == 0x1B)
	{
		//enter sequence
		_EscapeSequence();
		TERM_PF("<ESC key!>");
		return true;
	}
	//put the symbol into string
	if (!_AddToString(sym))
	{
		return false;
	}
	//echo the symbol to PC
	PutChar(sym);
	return true;
}

bool TERM_ExecCmd(void)
{
	Terminal_cmd_return_s execStat;
	if (!term.execFlag)
	{
		return false;
	}
	// parse the input string to [argc] [argv]
	_ParseInputStr(term.inputStr);
//	DBG("[%s]", term.inputStr);	// TODO: dbg injection
	// search for the command in fcn array
	if (_CmdSearch(inArgs.argv[0]))
	{
		execStat = _ExecCmd();
	}
	else
	{
		execStat = TERM_BadCmd;
	}
	switch(execStat)
	{
		case TERM_OK:
		{
			TERM_PF("\r\nCmd complete!");
		}break;
		case TERM_ExecErr:
		{
			TERM_PF("\r\nExecution error!");
		}break;
		case TERM_ArgErr:
		{
			TERM_PF("\r\nArguments error!");
		}break;
		case TERM_CmdCanceled:
		{
			TERM_PF("\r\nCmd canceled by user!");
		}break;
		case TERM_BadCmd:
		{
			TERM_PF("\r\nCmd does not exist!");
		}break;
	}
	// terminal should be reseted
	_ResetTerm();
	return true;
}

bool TERM_IsCanceled(void)
{
	// read cancel flag
	if (term.cancelFlag)
	{
		return true;
	}
	return false;
}

void TERM_Init(void)
{
	term.termPos = 0;
	term.execFlag = false;
	term.cancelFlag = false;
	term.cmdCount = 0;
	inArgs.argc = 0;
	for (uint8_t i = 0; i < MAX_ARGUMENTS_QTY; i++)
	{
		for (uint8_t j = 0; j < MAX_ARGUMENT_LENGTH; j++)
		{
			inArgs.argv[i][j] = 0;
		}
	}
	TERM_PF("\r\n*********************");
	TERM_PF("\r\n*<TERMINAL ver. 0.1>*");
	TERM_PF("\r\n*********************");
	_PrintArrows();
}

bool TERM_AddCmd(const char* strName, fcn execCode, uint8_t argNum, const char* strInfo)
{
	if (term.cmdCount > NUMBER_OF_COMMANDS)
	{
		return false;
	}
	term.termCmd[term.cmdCount].ExecCode = execCode;
	term.termCmd[term.cmdCount].info = strInfo;
	term.termCmd[term.cmdCount].name = strName;
	term.termCmd[term.cmdCount].argsNum = argNum;
	term.cmdCount++;
	return true;
}

bool TERM_GetArgDec(uint8_t argNum, uint32_t* val)
{
	volatile uint32_t getVal;
	char* str;
	argNum++;
	// check if argument number is valid
	if (argNum > term.termCmd[term.execIndex].argsNum)
	{
		return false;
	}
	// get from argv to string
	str = inArgs.argv[argNum];
	// forward string to atoi
	getVal = (uint32_t) atoi(str);
	// return value
	*val = getVal;
	return true;
}

bool TERM_GetArgStr(uint8_t argNum, char* str)
{
	argNum++;
	if (argNum > term.termCmd[term.execIndex].argsNum)
	{
		return false;
	}

	memset(str, 0, MAX_ARGUMENT_LENGTH);
	uint8_t cnt = 0;
	while(inArgs.argv[argNum][cnt] != '\0'){cnt++;}
	memcpy(str, inArgs.argv[argNum], cnt);

	return true;
}


bool TERM_GetArgHex(uint8_t argNum, uint32_t* val)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
static void _PrintArrows(void)
{
	PutChar('\r');
	PutChar('\n');
	PutChar('>');
	PutChar('>');
}

static bool _IsValid(char sym)
{
	// check if symbol is alphabet
	if ((sym >= 0x61) && (sym <= 0x7A))//check if symbol is alphabet
	{
		return true;
	}
	// enter or backspace or space or escape
	else if ((sym == 0x7F) || (sym == 0x0D) || (sym == 0x20) || (sym == 0x1B))
	{
		return true;
	}
	// is digit
	else if ((sym >= 0x30) && (sym <= 0x39))
	{
		return true;
	}
	else if (sym == '_')
	{
		return true;
	}
	else
	{
		return false;
	}
}

static bool _AddToString(char sym)
{
	//add symbol to the string
	if (term.termPos >= (MAX_INPUT_STR_LENGTH - 1))
	{
		return false;
	}
	term.inputStr[term.termPos] = sym;
	term.termPos++;
	return true;
}

static inline void _BackspaceSequence(void)
{
	if (term.termPos > 0)//check position
	{
		term.termPos--;
		PutChar(0x7F);
		//PutChar(TERM_PORT, 0x20);
	}
}

static inline void _EscapeSequence(void)
{
	term.cancelFlag = true;
}

static inline void _EnterSequence(void)
{
	//set the flag for the execution
	term.execFlag = true;
	term.inputStr[term.termPos] = 0x00;
}

static bool _ParseInputStr(char* str)
{
	uint16_t cnt = 0;
	uint8_t argStrPos = 0;
	inArgs.argc = 0;
	while((cnt < MAX_INPUT_STR_LENGTH) && (*(str + cnt) != 0x00))
	{
		if (*(str + cnt) == 0x20)
		{
			//if (inArgs.argc > 0)
			{
				inArgs.argv[inArgs.argc][argStrPos] = 0x00;
			}
			argStrPos = 0;
			inArgs.argc++;
		}
		else
		{
			inArgs.argv[inArgs.argc][argStrPos] = *(str + cnt);
			argStrPos++;
		}
		cnt++;
	}
	inArgs.argc++;
//	DBG("[%i] [%s] [%s] [%s]", inArgs.argc, inArgs.argv[0], inArgs.argv[1],inArgs.argv[2]);// TODO: dbg injection
	return true;
}

static bool _CmdSearch(char* str)
{
	//set the index in function pointers array
	for (uint8_t i = 0; i < term.cmdCount; i++)
	{
		if (_StringCmp(str, term.termCmd[i].name))
		{
			term.execIndex = i;
			return true;
		}
	}
	return false;
}

static Terminal_cmd_return_s _ExecCmd(void)
{
	Terminal_cmd_return_s cmdReturn;
	if (term.termCmd[term.execIndex].argsNum != (inArgs.argc - 1))
	{
		return TERM_ArgErr;
	}
	cmdReturn = term.termCmd[term.execIndex].ExecCode();
	return cmdReturn;
}

static bool _StringCmp(const char* str1,const  char* str2)
{
	uint8_t cnt = 0;
	while ((*(str1 + cnt) != 0x00) || (*(str2 + cnt) != 0x00))
	{
		if (*(str1 + cnt) != *(str2 + cnt))
		{
			return false;
		}
		cnt++;
	}
	return true;
}

static void _ClearArg(char* str)
{
	for (uint8_t i = 0; i < MAX_ARGUMENT_LENGTH; i++)
	{
		str[i] = 0x00;
	}
}

static bool _ResetTerm(void)
{
	term.termPos = 0;
	term.execFlag = false;
	term.cancelFlag = false;
	inArgs.argc = 0;
	for (uint8_t i = 0; i < MAX_ARGUMENTS_QTY; i++)
	{
		_ClearArg(inArgs.argv[i]);
	}
	_PrintArrows();
	return true;
}

