#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[0])
{
    if(argc < 2) {
        printf("[Error]: Bitte Zahl/en eingeben!\n");
        exit(EXIT_FAILURE);
    }

    for(int zahl = 1; zahl < argc; ++zahl) {
        unsigned int input = atoi(argv[zahl]);
        printf("%10u: ", input);

        for(int i = 28; i >= 0; i -=4) {
            unsigned int n = (input >> i) & 0xf;

            char ziffer[16] = "0123456789ABCDEF";
            putchar(ziffer[n]);
            
            if(i == 16) putchar(' ');
        }

        putchar(' ');
        putchar(' ');

        for(int i = 31; i >= 0; --i) {
            unsigned int n = (input >> i) & 1;

            putchar('0' + n);

            if((i & 3) == 0) {
                putchar(' ');
            }
        }

        putchar('\n');
    }

    exit(EXIT_SUCCESS);
}