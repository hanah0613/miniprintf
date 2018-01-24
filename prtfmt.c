#include <stdarg.h>
#include <unistd.h>
#include "prtfmt.h"

static char * _itoa(int n, char *b, int radix)
{
	int i;
	int deg=1;
	int c=0;

	while(1){
		if( (n/deg) > 0 )
			c++;
		else
			break;
		deg*=radix;
	}
	
	for(i=0;i<c;i++) {
		*(b+i) = n/deg + '0';
		n -= ((n/deg) *deg);
		deg/=radix;
	}
	*(b+i)='\0';

	return b;
}

static size_t _strlen(const char *s) 
{
	size_t count=0;
	while(s[count]!='\0') {
		count++;
	}
	return count;
} 

static void *_memset(void *s, int c, size_t n) 
{
	char *ps=(char *)s;
	while(n--) ps[n]=c;
	
	return s;
}

static void *_memcpy(void *d,const void *s, size_t n)
{
	char *pd=(char *)d;
	const char *ps=(char *)s;
	while(n--) *pd++=*ps;

	return d;
}
static TYPE _check_type(int flag, char type) 
{
	switch(type){
		case 'c':
			if((flag&SHORT) | (flag&LONG)) return ERROR;
			return CHAR;
			break;
		case 's':
			if((flag&SHORT) | (flag&LONG)) return ERROR;
			return STRING;
			break;
		case 'b':
			return BINARY;
			break;
		case 'd':
			return DECIMAL;
			break;
		case 'x':
			return HEX_LOW;
			break;
		case 'X':
			return HEX_UP;
			break;
		default:
			return NONE;
			break;
	}
}

static char * _check_flag(int *width,int flag,char *p) 
{
	int i=1;
	while(i) {
		p++;
		switch (*p) {
			case '~':
				flag|=REVERSE;
				break;
			case '+':
				flag|=POSITIVE;
				break;
			case '-':
				flag|=NEGATIVE;
				break;
			case '0':
				flag|=FILLZERO;
				break;
			case '1' ... '9':
				{
					int tmp;
					tmp=*p-'0';
					if(*width)
						*width*=10;	
					width+=tmp;
					flag|=WIDTHOFPRT;
				}
			case '.':
				flag|=CUT_STR;
				break;
			case 'h':
				flag|=SHORT;
				break;
			case 'l':
				flag|=LONG;
				break;
			default:
				i=0;
				break;
		}	
	}
	return ++p;
}

int mini_printf(const char *fmt, ...)
{
	char *p;
	int width=0;
	int fmt_len = _strlen(fmt);
	int flag = 0x00;
	TYPE type=NONE; 
	va_list arg_p;
	

	va_start(arg_p, fmt);
	for (p=fmt ; '\0'!=p ; p++) {
		if(*p!='%') {

			continue;	
		}

		p=_check_flag(&width,flag,p);
		if((type=_check_type(flag,*p))<=NONE) continue;
	}

	return 0;
}
