#include "include/util.h"

char * _tolowercase(char *s)
{
	int a=_strlen(s);
	int i;	
	for (i = 0; i < a; ++i) {
		if(*(s+i)<'A'||*(s+i)>'Z')
			continue;
		*(s+i)+='a'-'A';
	}

	return s;
}

char * _itoa(long int n, char *b, int radix)
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
		if(*(b+i)>'9') {
			*(b+i)=n/deg+'A'-10;
		}
		n-=((n/deg)*deg);
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
