#ifndef _UTIL_H_
#define _UTIL_H_

#define NULL ((void*)0)

#define STDOUT 1
#define STDERR 2 

typedef unsigned long size_t;

char * _itoa(int n, char *b, int radix);
int _atoi(char *s);
size_t _strlen(const char *s);
char *_strtok(char *s, const char *d);
int _check_to_width(char *s, const char *d);
void *_memset(void *s, int c, size_t n);
void *_memcpy(void *d,const void *s, size_t n);
#endif