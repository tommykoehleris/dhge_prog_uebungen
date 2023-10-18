#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    int r = atoi(argv[1]);
    int k = atoi(argv[2]);
    int facher = r + 1;

    int array[facher];

    for (int i = 0; i < facher; i++)
    {
        array[i] = 0;
    }



    for(int i = 0; i < k; i++)
    {
        int anzahl_rechts = 0;
        for (int j = 0; j < r; ++j)
        {
            int links_rechts = rand() % 2 + 0;

            if(links_rechts == 1)
            {
                anzahl_rechts++;
            }
        }

        array[anzahl_rechts]++;
    }

    int max = 0;

    for (int i = 0; i < facher; i++)
    {

        if(array[i] >= max)
        {
            max = array[i];
        }
        //printf(" %d ", array[i]);
    }

    double faktor = 65. / max;

    //printf("%g\n", faktor);

    for (int i = 0; i < facher; i++)
    {
        printf("%8d ", array[i]);

        double anzahl_raute = array[i] * faktor;

        for(int j = 0; j < anzahl_raute; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
