#include <stdio.h>
#include <stdlib.h>

void sortiere(int a[], int n);

void sortiere(int a[], int n)
{
    int ende = n - 1;

    while (ende > 0) {
        int zuletzt_getauscht = 0;

        for (int i = 0; i < ende; i++) {
            if (a[i] > a[i + 1]) {
                int hv = a[i];
                a[i] = a[i + 1];
                a[i + 1] = hv;
                zuletzt_getauscht = i;
            }
        }
        ende = zuletzt_getauscht;
    }
}

int main(int argc, const char *argv[])
{
    int array_size = argc - 1;
    int array[argc];

    for (int i = 0; i < array_size; i++) {
        array[i] = atoi(argv[i + 1]);
    }

    sortiere(array, array_size);

    for (int i = 0; i < array_size; ++i) {
        printf("%d ", array[i]);
    }

    return 0;
}

