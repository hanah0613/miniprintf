
#ifndef _PRTFMT_H_
#define _PRTFMT_H_

#define REVERSE  0x01
#define POSITIVE 0x02
#define NEGATIVE 0x04
#define FILLZERO 0x08

#define SHORT 0x01
#define LONG  0x02

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
