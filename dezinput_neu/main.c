#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int my_strtol(const char zeichen[], char **endp);

int my_strtol(const char zeichen[], char **endp) 
{
    int z = 0;
    

    for(; isdigit(*zeichen); ++zeichen) {
        z = (10 * z) + (*zeichen -'0');
    }

    if(endp != NULL) {
        *endp = zeichen;
    }

    return z;
}

int main(int argc, const char *argv[]) 
{
    if(argc == 1) {
        fprintf(stderr, "[ERROR]: Zu wenig Argumente auf Befehlszeile.");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= argc; ++i) {
        char *ende;
        printf("%s = %d\n", argv[i], my_strtol(argv[i], &ende));
        while(ende != '\0') {
            
        //if(*ende != '\0') {
            printf("[INFO]: REST: %s: ZAHL = %d", ende, my_strtol(argv[i], &ende));                
        }
        //} else {
        putchar('\n');
    }

    exit(EXIT_SUCCESS);
}