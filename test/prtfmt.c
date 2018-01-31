#include <stdarg.h>
#include <unistd.h>
#include "prtfmt.h"
#include "util.h"

#define CHECK_WIDTH_DEL ".csbdxX\0"
#define CHECK_PRECISION "csbdxX\0"

int width;
int flag;
int precision;
int type_prefix;
TYPE type; 

static char * _check_flag(char *p) 
{
	int i=1;
	while(i) {
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
			default:
				i=0;
				break;
		}	
		p++;
	}
	return --p;
}

static char* _check_width(char *p)
{
	const char *del=CHECK_WIDTH_DEL;
	int i=0;
	int tmp=0;
	int check_del=0

	if(p==NULL)
		return i;
	
	for(;*p;p++) {
		for(;*p;p++){
			if(*p==*del){
				check_del=1;
				break;
			} 
				
			tmp=*ps-'0';
			if(i)	
				i*=10;
			i+=tmp;
		}
		if(check_del) break;
	}
	width=i;
	return p;
}

static char* _check_precision(char *p)
{
	int i=0;
	int tmp=0;
	char *del=CHECK_PRECISION;

	if(*p=='.') {
		for(p++;*p;p++) {
			if(*p==*del) break; 
				
			tmp=*ps-'0';
			if(i)	
				i*=10;
			i+=tmp;
		}
	}

	precision=i;
	return p;
}

static char* _check_type_prefix(char *p)
{
	if(*P=='h'){
		type_prefix|=SHORT;
	} else if(*p=='l'){
		type_prefix|=LONG;
	} else {
		return p;
	}

	P++;
	return p;
}

static TYPE _check_type(char *p) 
{
	switch(*p){
		case 'c':
			if((type_prefix) return ERROR;
			return CHAR;
			break;
		case 's':
			if(type_prefix) return ERROR;
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
			if(flag || width || precision || type_prefix) return ERROR;
			return NONE;
			break;
	}
}

static void _print_decimal(int i)
{
	char buf[12];
	int len;
	_memset((void *)buf, '\0', 12);
	_itoa(i, buf,10);

	len=_strlen(buf);
	write(STDOUT,buf,len);
}

int mini_printf(char *fmt, ...)
{
	char *p;
	long long int cnt=0;
	width=0;
	flag=0;
	precision=0;
	type_prefix=0;
	type=NONE; 
	int fmt_len=_strlen(fmt);
	va_list arg_p;
	
	va_start(arg_p, fmt);
	
	for (p=fmt ; '\0'!=p && cnt < fmt_len ; p++, cnt++) {
		if(*p!='%') {
			write(STDOUT,p,1);
			continue;
		}
		p++;
		
		p=_check_flag(p);
		p=_check_width(p);
		p=_check_precision(p);
		p=_check_type_prefix(p);
		
		if((type=_check_type(*p))==NONE) {
			
			continue;
		}
		else if((type=_check_type(*p))==ERROR) {
		
			continue;
		} 

		switch(type) {
			
			case DECIMAL: 
			{
				int a = va_arg(arg_p, int);
				_print_decimal(flag,a);
			}
			case CHAR: 
			case STRING:
			case BINARY: 
			case HEX_LOW: 
			case HEX_UP:
			default:
				break;
		}
	}

	va_end (arg_p);
	return 0;
}
