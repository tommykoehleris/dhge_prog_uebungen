#include <stdio.h>
#include <stdlib.h>

unsigned int aufrufe = 0;

unsigned int binom(unsigned int n, unsigned int k)
{
    static unsigned int array[35][35];

    ++aufrufe;

    if (n > 35) {
        printf("Zu großer Wert für n!");
    }

    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    if (array[n][k] != 0) {
        return array[n][k];
    }
    else {
        unsigned int hv = binom(n - 1, k - 1) + binom(n - 1, k);
        array[n][k] = hv;
        return hv;
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        printf("Aufruf: %s n k\n", argv[0]);
        return 1;
    }

    printf("%s uber %s = %u \n", argv[1], argv[2], binom(atoi(argv[1]), atoi(argv[2])));
    printf("Funktionsaufrufe: %u", aufrufe);

    return 0;
}
