#include <stdarg.h>
#include <unistd.h>
#include "prtfmt.h"

char *check_del=".csbdxX";

static char * _itoa(int n, char *b, int radix)
{
	int i;
	int deg=1;
	int c=0;

	while(1) {
		if( (n/deg) > 0 )
			c++;
		else
			break;
		deg*=radix;
	}
	deg/=radix;
	for(i=0;i<c;i++) {
		*(b+i) = n/deg + '0';
		n-=((n/deg) *deg);
		deg/=radix;
	}
	*(b+i)='\0';

	return b;
}

static int _atoi(char *s)
{
	int i;
	int tmp;
	for(i=0;*s!='\0';s++) {
		i=*s-'0';
		tmp*=10;
		tmp+=i;
	}
	return tmp;
}

static size_t _strlen(const char *s) 
{
	size_t count=0;
	while(s[count]!='\0') {
		count++;
	}
	return count;
} 

static char *_strtok(char *s, const char *d)
{
	static char *ps;
	const char *pd;

	if(s==NULL) 
		s=ps;
	else 
		ps=s;

	for(;*ps;ps++) {
		for(pd=d;*pd;pd++) {
			if(*ps==*pd)
			{
				ps='\0';
				ps++;
				return s
			}
		}
	}	
	return s;
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
					char buf=_strtok(*p,check_del);
					*width=_atoi(buf);
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

static void _print_char(char a, int flag)
{

}

static void _print_string(char *s, int flag)
{

}

static void _print_decimal(int i, int flag)
{

}

#if 0
static void _print_binary(int i, int flag)
{

}

static void _print_hex(int i, flag)
{

}
#endif

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
			write(STDOUT,*p,1);
			continue;	
		}
		p++;
		p=_check_flag(&width,flag,p);
		if((type=_check_type(flag,*p))<=NONE) continue;
		
		switch(type) {
			case CHAR: {
				char a = va_arg(arg_p, char);
				_print_char(a, flag);
			}
				break;
			case STRING: {
				char *a = va_arg(arg_p, char *);
				_print_string(a, flag);
			} 
				break;
			case BINARY: 
			case DECIMAL: 
			case HEX_LOW: 
			case HEX_UP: {
				if(flag&SHORT)
					short int a = va_arg(arg_p, short int);
				else if(flag&LONG)
					long int a = va_arg(arg_p, long int);
				else 
					int a = va_arg(arg_p, int);
				_print_decimal(a, flag);
			}
				break;
		}
	}

	va_end (arg_p);
	return 0;
}
