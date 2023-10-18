#include <stdio.h>
#include <stdlib.h>

void rek(int zahl);

int main(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        rek(atoi(argv[i]));
        putchar('\n');
    }

    return 0;
}

void rek(int zahl)
{
    if (zahl < 0) {
        putchar('-');
        zahl = -zahl;
    }
    putchar(zahl % 10 + '0');

    if (zahl > 9) {
        rek(zahl / 10);
    }
 }
