#include "string_my.h"
#include <stdio.h>

int strlen(const char *str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;
    return i;
}

int puts_my(const char* str)
{
    char n[] = "\n";
    if(fwrite(str, sizeof(char), sizeof(str) / sizeof(char), stdout) == (sizeof(str) / sizeof(char)) && fwrite(n, sizeof(char), 1, stdout) == 1)
        return '\n';
    else
        return -1;
}
