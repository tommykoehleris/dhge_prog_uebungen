#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool minmax(double array[], int size, double *minP, double *maxP);

bool minmax(double array[], int size, double *minP, double *maxP)
{
    if(size <= 0) {
        return false;
    }

    *minP = *maxP = array[0];

    for(int i = 0; i < size; ++i) {
        if(array[i] < *minP) {
            *minP = array[i];
        }
        if(array[i] > *maxP) {
            *maxP = array[i];
        }
    }
    return true;
}

int main (int argc, const char *argv[])
{
    if(argc == 1)
    {
        fprintf(stderr, "[ERROR]: Too few Arguments.");
        exit(EXIT_FAILURE);
    }
    
    double array[argc];

    double min;
    double max;     

    for(int i = 0; i < argc; ++i)
    {
        array[i - 1] = atof(argv[i]);
    }

    if(minmax(array, argc - 1, &min, &max) == true)
    {
        printf("Minimum: %g / Maximum: %g\n", min, max);
    } else {
        fprintf(stderr, "[ERROR]: minmax Error.");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}