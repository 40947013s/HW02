#ifndef MYSPLIT_H_INCLUDE
#define MYSPLIT_H_INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int mystrsplit(char ***ppList , int *pCounter , const char *pStr, const char *
pSeparator);

#endif