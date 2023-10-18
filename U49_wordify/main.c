#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LEN 82

int func(const char str[], int *pos)
{
    int start = *pos;
    int end = 0;
    
    for(start = *pos; !isalnum(str[start]); ++start) {
        if(str[start] == '\0') {
            *pos = start;
            return -1;
        }
    }

    for(end = start + 1; isalnum(str[end]); ++end) {}
    *pos = end;

    return start;
}

int main(void) 
{
    char zeile[LINE_LEN];

    while(fgets(zeile, sizeof(zeile), stdin)) {
        int tmppos = 0;
        for(; ;) {
            int wordpos = func(zeile, &tmppos);    
            if(wordpos == -1) break;

            for(int i = wordpos; i < tmppos; ++i) {
                putchar(zeile[i]);
            }
            putchar('\n');
        }
    }
}