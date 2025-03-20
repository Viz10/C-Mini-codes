#ifndef MYFUNC_H
#define MYFUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define MY_FUNC(a,b,type){ \
type my_##type = (a)+(b);\
printf("%s,%s", #a, #b); \
printf("\nsum:%d\n", my_##type);\
}\

// # = numele ca string al varibilei ce a fost trimisa

size_t getline(char**, int*, FILE*);
size_t getdelim(char** , int* , int , FILE* );
char* strsep(char**, char*);

size_t myStrlen(const char*);
void* myMemcpy(void*, const void*, size_t);
int myMemcmp(const void* , const void* , size_t );
int myAtoi(const char*);
char* myStrcat(char* ,const char* );
const char* myStrstr(const char*, const char*);
void* myMemmove(void* , const void* , size_t );
void* myMemset(void* ptr ,int , size_t );
size_t myStrspn(const char* , const char* );


void sort_string(char*, int);

#endif 

