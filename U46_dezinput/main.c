#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int eigenes_strtol(const char str[], char **endp)
{
    int z = 0;

    for ( ; isdigit(*str); ++str) {
        z = (10 * z) + (*str - '0');
    }

    if(endp != NULL) {
        *endp = str;
    }

    return z;
}

int main(int argc, const char *argv[]) 
{
    if(argc == 1) {
        printf("Aufruf: %s !\n", argv[0]);
        return 1;
    }

    for(int i = 0; i < argc; ++i) {
        char *ende;
        printf("%s = %d", argv[i], eigenes_strtol(argv[i], &ende));
        if (*ende != '\0') {
            printf(", Rest des Wortes: \"%s\"\n", ende);
        }
        else {
            printf("\n");
        }
    }
}

