#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[]) 
{
    if(argc != 2) {
        printf("[ERROR]: Eingabe prüfen! (genau 1 Zahl eingeben)");
        exit(EXIT_FAILURE);
    }

    unsigned short input, original, reverse, byte; 
    input = original = atoi(argv[1]);
    reverse = 0;

    for(int i = 0; i < sizeof(input); ++i) {
        byte = input & 0xff;
        input >>= 8;
        reverse <<= 8;
        reverse |= byte;
    }

    printf("Original: %08hx, Reverse Swapped: %08hx", original, reverse);

    exit(EXIT_SUCCESS);
}