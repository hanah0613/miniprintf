#include "util.h"

char * _itoa(int n, char *b, int radix)
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

int _atoi(char *s)
{
	int i;
	int tmp=0;
	for(i=0;*s!='\0';s++) {
		i=*s-'0';
		if(tmp)
			tmp*=10;
		tmp+=i;
	}
	return tmp;
}

size_t _strlen(const char *s) 
{
	size_t count=0;
	while(s[count]!='\0') {
		count++;
	}
	return count;
} 

char *_strtok(char *s, const char *d)
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
				*ps='\0';
				ps++;
				return s;
			}
		}
	}	
	return s;
}

int _check_to_width(char *s, const char *d)
{
	char *ps;
	const char *pd;
	int i=0;
	int tmp=0;

	if(s==NULL)
		return i;
	else
		ps=s;
	
	for(;*ps;ps++) {
		for(pd=d;*pd;pd++){
			if(*ps==*pd) break;
				
			tmp=*ps-'0';
			if(i)	
				i*=10;
			i+=tmp;
		}
	}
	return i;
}

void *_memset(void *s, int c, size_t n) 
{
	char *ps=(char *)s;
	while(n--) ps[n]=c;
	
	return s;
}

void *_memcpy(void *d,const void *s, size_t n)
{
	char *pd=(char *)d;
	const char *ps=(char *)s;
	while(n--) *pd++=*ps;

	return d;
}