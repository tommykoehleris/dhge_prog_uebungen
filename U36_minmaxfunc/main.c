#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool minmaxfunc(const double array[], int anz_elem, double *minP, double *maxP)
{
    if(anz_elem <= 0) return false;
    
    *minP = *maxP = array[0];

    for(int i = 1; i < anz_elem; i++)
    {
        if(array[i] < *minP)
        {
            *minP = array[i];
        }
        if(array[i] > *maxP) 
        {
            *maxP = array[i];
        }
    }

    return true;
}

int main(int argc, const char *argv[])
{   
    int anz_elem = argc - 1;
    double array[argc];
    double min, max;//variablen für die funktion

    for (int i = 1; i < argc; i++)
    {
        array[i - 1] = atof(argv[i]);
    }

    int erfolg = minmaxfunc(array, anz_elem, &min, &max);

    if (erfolg == 1)
    {
        printf("Minimum: %g, Maximum: %g\n", min, max);
        return 0;
    }
    else {
        printf("Kein Minimum und Maximum.\n");
        return 1;
    }
}
