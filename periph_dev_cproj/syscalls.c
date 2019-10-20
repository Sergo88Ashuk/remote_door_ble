/*
 * syscalls.c
 *
 *  Created on: 8 èþë. 2018 ã.
 *      Author: lvr_laptop
 */

#include <sys/stat.h>
#include "lvr_uart.h"

void outbyte(char sym)
{
	UARTLVR_PutSym(sym);
}

int _close(int file)
{
	return -1;
}

int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	return 1;
}

long _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _read(int file, char* ptr, int len)
{
	return 0;
}

int _write(int file, char* ptr, int len)
{
	int todo;
	for (todo = 0; todo < len; todo++) {
	outbyte(*ptr++);
	}
	return len;
}

