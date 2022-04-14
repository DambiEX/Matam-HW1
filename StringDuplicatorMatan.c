#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* stringDuplicator(char* str, int times)
{
    assert(str);
    assert(times > 0);
    int len = strlen(str);
    char* out = malloc(sizeof(int*)*len*times);
    assert(out);
    for (int i = 0; i < times; i++)
    {
        out = out + len;
        strcpy(out,str);
    }
    return out;
}