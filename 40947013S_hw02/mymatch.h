#ifndef MYMATCH_H_INCLUDE
#define MYMATCH_H_INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool match(char *word, const char *pStr);
int mymatch(char ***pppList , const char *pStr, const char *pPattern);

#endif