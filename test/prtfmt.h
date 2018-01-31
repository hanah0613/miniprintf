
#ifndef _PRTFMT_H_
#define _PRTFMT_H_

typedef	enum {
	ERROR=-1,
	NONE=0,
	CHAR=1,
	STRING,
	BINARY,
	DECIMAL,
	HEX_LOW,
	HEX_UP
} TYPE;

int mini_printf(char *fmt, ...);

#endif
