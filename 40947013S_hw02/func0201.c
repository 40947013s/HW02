#include "mysplit.h"
#include "mymatch.h"

int mystrsplit(char ***ppList , int *pCounter , const char *pStr, const char *
pSeparator)
{
    if(pStr == NULL || pSeparator == NULL) return -1; //無東西切割
    char *copy = calloc(strlen(pStr)+1, sizeof(char)); 
    strncpy(copy, pStr, strlen(pStr)); //複製pStr
    if( strlen(pSeparator) == 0) //分割符為NULL(視為" "")
    {
        char *token = strtok(copy, " ");
        while(token != NULL)
        {
            (*pCounter)++; token = strtok(NULL, " ");
        }
        *ppList = calloc(*pCounter, sizeof(char*));
        strncpy(copy, pStr, strlen(pStr));
        token = strtok(copy, " ");
        int count = 0;
        while(token != NULL)
        {
            char *copy_token = calloc(strlen(token)+1, sizeof(char));
            for(int i = 0; i < strlen(token); i++)
                copy_token[i] = token[i];
            copy_token[strlen(token)] == 0;
            *(*ppList+count) = copy_token;
            token = strtok(NULL, " "); count++;
        }
        return 0;
    }
    if(strstr(copy, pSeparator) == NULL)
    {
        *ppList = calloc(1, sizeof(char*));
        **ppList = calloc(strlen(pStr)+1, sizeof(char));
        *(*ppList) = (char*)pStr;
        *pCounter = 1; return 0;
    }

    int table[100]; table[0] = strlen(pStr)-strlen(pSeparator)+1;
    do{
        char *replace = calloc(strlen(pStr)+1, sizeof(char));
        strcpy(replace, strstr(copy, pSeparator));
        replace += strlen(pSeparator);
        strcpy(copy, replace);
        table[(*pCounter)+1] = strlen(copy); (*pCounter)++;
    }while(strstr(copy, pSeparator) != NULL);
    (*pCounter)++; 
    
    *ppList = calloc(*pCounter, sizeof(char*)); 
    int *length = calloc(*pCounter, sizeof(int));
    for(int i = 0; i < (*pCounter); i++)
    {
        int start = (i == 0) ? 0 : strlen(pStr)-table[i];
        int end = (i != (*pCounter)-1) ? strlen(pStr)-table[i+1]-strlen(pSeparator) : strlen(pStr);
        length[i] = end - start; 
        if(length[i] == 0) 
        {
            char *copy = "";
            *(*ppList+i) = copy; continue;
        }
        char *copy = calloc(length[i]+1, sizeof(char));
        int32_t count = 0;
        for(int j = start; j < end; j++)
            copy[count++] = pStr[j];
        *(*ppList+i) = copy;
    }
    return *pCounter == 1 ? -1 : 0;
}


bool match(char *word, const char *pStr) 
{
    char *back_word = NULL, *back_pStr = NULL;    
    while(strlen(word) != 0 && *pStr != '*') 
    {
        if (*pStr != *word && *pStr != '?') return 0;
        pStr++, word++;
    }        
    while(strlen(word) != 0) 
    {
        if(*pStr == '*') 
        {
            pStr++;
            if (strlen(pStr) == 0) return 1;
            back_pStr = (char*)pStr, back_word = word++;
        } 
        else if(*pStr == *word || *pStr == '?') pStr++, word++;
        else pStr = back_pStr, word = back_word++;
    }        
    while(*pStr == '*') pStr++;
    return strlen(pStr) == 0;
}

int mymatch(char ***pppList , const char *pStr, const char *pPattern)
{
    char **word, *str;
    int size = 0, count = 0; 
    mystrsplit(&word, &size, pPattern, " ");
    for(int i = 0; i < size; i++)
    {
        if(word[i] == 0) return -1;
        else if(match(word[i], pStr)) count++;
    }
    *pppList = calloc(count, sizeof(char*));
    count = 0;
    for(int i = 0; i < size; i++)
    {
        if(match(word[i], pStr)) 
        {
            *(*pppList+count) = word[i];
            count++;
        }
    }
    return count == 0 ? -1 : count;
}



