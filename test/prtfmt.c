#include <stdarg.h>
#include <unistd.h>
#include "include/prtfmt.h"
#include "include/util.h"

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
	int i=0;
	int tmp=0;

	if(p==NULL)
		return NULL;
	
	if(*p<'0'||*p>'9') return p;

	for(;*p;p++,(*cnt)++){
		if(*p<'0' || *p>'9') break;
			
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

	if(p==NULL)
		return NULL;

	if(*p=='.') {
		flag|=SET_PRE;
		for(p++,(*cnt)++;*p;p++,(*cnt)++) {
			if(*p<'0' || *p>'9') break;
				
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

static void _do_flag(int len, char *buf) {
	char sign=0;
	switch (type) {
		case DECIMAL:
			{
				if(*buf=='-') sign='-';
				else if(flag&POSITIVE) {
					sign='+';
					width--;
				}
			}	
		case BINARY:
		case HEX_LOW:
		case HEX_UP:
		case STRING:
			{
				char tmp;
				if(flag&FILLZERO) {
					if(sign=='-') { 
						_memcpy((void *)buf,(void *)buf+1,len);
						write(STDOUT,&sign,1);
					} else if(flag&POSITIVE) {
						write(STDOUT,&sign,1);
					}
					tmp='0';
				}
				else 
					tmp=' ';
				int i;
				int a=(precision)?precision:width;
				a-=len;
				for(i=0;i<a;i++) {
					write(STDOUT,&tmp,1);	
				}
			}
			if(type!=STRING) break;
			if(flag&REVERSE)
			 _reverse_str(buf);	
		default:
			break;
	}
}

static void _write_before(int len, char *buf) {
	if(width<len) return;
	if(flag&NEGATIVE) return;
	int i;
	int a=(precision)?precision:len;
	int t=width-a;

	for(i=0;i<t;i++) {
		if(!(flag&SET_PRE)) break;
		char tmp=' ';
		write(STDOUT,&tmp,1);
	}

	_do_flag(len, buf);

	return;
}

static void _write_after(int len){
	if(!(flag&NEGATIVE)) return;
	int i;

	for (i=len; i<width; i++) {
		char tmp=' ';
		write(STDOUT,&tmp,1);
	}
	return;
}

static void _print_number(long int d)
{
	char buf[NUM_SIZE];
	int len=0;
	
	_memset((void *)buf, '\0',NUM_SIZE);
	switch (type) {
		case DECIMAL:
			_itoa(d,buf,10);
			break;
		case BINARY:
			_itoa(d,buf,2);
			flag|=FILLZERO;
			break;
		case HEX_LOW:
		case HEX_UP:
			_itoa(d,buf,16);
			if(type==HEX_LOW)
				_tolowercase(buf);
			break;
		case CHAR:
			buf[0]=d;
			break;
		default:
			break;
	}

	if(d<0) width--;	
	len=_strlen(buf);
	_write_before(len,buf);
	write(STDOUT,buf,len);
	_write_after(len);
}

static void _print_string(char *buf) {
	int len=0;

	len=_strlen(buf);
	if(flag&SET_PRE) len=precision;

	_write_before(len,buf);
	write(STDOUT,buf,len);
	_write_after(len);
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
			case CHAR: 
			{
				if(flag&LONG) {
					long int a = va_arg(arg_p, long int);
					_print_number(a);
					break;
				}
				int a = va_arg(arg_p, int);
				_print_number(a);
			}
				break;
			case STRING:
			{
				char *tmp = va_arg(arg_p, char *);
				_print_string(tmp);
			}
				break;
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
