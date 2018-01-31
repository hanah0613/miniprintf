#include <stdarg.h>
#include "prtfmt.h"
#include "util.h"

int mini_printf(char *fmt, ...)
{
	char *p;
	int width=0;
	int fmt_len = _strlen(fmt);
	int flag = 0x00;
	TYPE type=NONE; 
	va_list arg_p;
	
	va_start(arg_p, fmt);
	
	for (p=fmt ; '\0'!=p ; p++) {
		write(STDOUT,p,1);
	}

	va_end (arg_p);
	return 0;
}
