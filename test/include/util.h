#ifndef _UTIL_H_
#define _UTIL_H_

#ifndef NULL
#define NULL ((void*)0)
#endif

#define STDOUT 1
#define STDERR 2 

typedef unsigned long size_t;

char * _tolowercase(char *s);
char * _itoa(long int n, char *b, int radix);
int _atoi(char *s);
size_t _strlen(const char *s);
char *_strtok(char *s, const char *d);
int _check_to_width(char *s, const char *d);
void *_memset(void *s, int c, size_t n);
void *_memcpy(void *d,const void *s, size_t n);
void _reverse_str(char *str);
#endif
