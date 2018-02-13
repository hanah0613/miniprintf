#include <stdarg.h>
#include <unistd.h>
#include "include/prtfmt.h"
#include "include/util.h"

#define CHECK_WIDTH_DEL ".csbdxX%\0"
#define CHECK_PRECISION "csbdxX%\0"

int width;
int flag;
int precision;
int type_prefix;
TYPE type; 

static char * _check_flag(char *p, long long int *cnt) 
{
	int i=1;

	if(p==NULL)
		return NULL;

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
		(*cnt)++;
	}

	(*cnt)--;
	return --p;
}

static char* _check_width(char *p,long long int *cnt)
{
	const char *del=CHECK_WIDTH_DEL;
	int i=1;
	int tmp=0;

	if(p==NULL)
		return NULL;
	
	if(*p<'0'||*p>'9') return p;

	for(;*p;p++,(*cnt)++){
		if(*p==*del || *p<'0' || *p>'9'){
			break;
		} 
			
		tmp=*p-'0';
		if(i)	
			i*=10;
		i+=tmp;
	}
	width=i;
	return p;
}

static char* _check_precision(char *p,long long int *cnt)
{
	int i=0;
	int tmp=0;
	char *del=CHECK_PRECISION;

	if(p==NULL)
		return NULL;

	if(*p=='.') {
		for(p++,(*cnt)++;*p;p++,(*cnt)++) {
			if(*p==*del) break; 
				
			tmp=*p-'0';
			if(i)	
				i*=10;
			i+=tmp;
		}
	}

	precision=i;
	return p;
}

static char* _check_type_prefix(char *p,long long int *cnt)
{
	if(*p=='h'){
		type_prefix|=SHORT;
	} else if(*p=='l'){
		type_prefix|=LONG;
	} else {
		return p;
	}

	p++;
	(*cnt)++;
	return p;
}

static TYPE _check_type(char *p) 
{
	switch(*p){
		case 'c':
			if(type_prefix) return ERROR;
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
		case '%':
			return PERCENT;
			break;
		default:
			if(flag || width || precision || type_prefix) return ERROR;
			return NONE;
			break;
	}
}

static void _print_decimal(long int i)
{
	char buf[12];
	int len;
	_memset((void *)buf, '\0', 12);
	switch (type) {
		case DECIMAL:
			_itoa(i,buf,10);
			break;
		case BINARY:
			_itoa(i,buf,2);
			break;
		case HEX_LOW:
		case HEX_UP:
			_itoa(i,buf,16);
			if(type==HEX_LOW)
				_tolowercase(buf);
			break;
		default:
			break;
	}

	len=_strlen(buf);
	write(STDOUT,buf,len);
}

int mini_printf(char *fmt, ...)
{
	char *p;
	long long int cnt=0;
	int fmt_len=_strlen(fmt);
	va_list arg_p;
	
	va_start(arg_p, fmt);

	for (p=fmt ; '\0'!=p && cnt < fmt_len ; p++, cnt++) {
		if(*p!='%') {
			write(STDOUT,p,1);
			continue;
		}
		p++;
		cnt++;

		width=0;
		flag=0;
		precision=0;
		type_prefix=0;
		type=ERROR; 

		p=_check_flag(p,&cnt);
		p=_check_width(p,&cnt);
		p=_check_precision(p,&cnt);
		p=_check_type_prefix(p,&cnt);
		
		type=_check_type(p);

		if(type==NONE) {
			char tmp='%';
			write(STDOUT,&tmp,1);
			write(STDOUT,p,1);
			continue;
		}
		else if(type==ERROR) 
			continue;

		switch(type) {
			case DECIMAL: 
			case BINARY: 
			case HEX_LOW: 
			case HEX_UP:
			{
				if(flag) {
					if(flag&LONG) {
						long int a = va_arg(arg_p, long int);
						_print_decimal(a);
						break;
					}
				}
				int a = va_arg(arg_p, int);
				_print_decimal(a);
				break;
			}
			case CHAR: 
			case STRING:
			case PERCENT:
			{
				char tmp='%';
				write(STDOUT,&tmp,1);
			}	
				break;
			default:
				break;
		}
	}

	va_end (arg_p);
	return 0;
}
