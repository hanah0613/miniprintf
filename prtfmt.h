
#define REVERSE 0x01
#define POSITIVE 0x02
#define NEGATIVE 0x04
#define FILLZERO 0x08
#define CUT_STR 0x0f
#define SHORT 0x10
#define LONG 0x20
#define WIDTHOFPRT 0x40

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

typedef unsigned long size_t;
int mini_printf(const char *fmt, ...);
