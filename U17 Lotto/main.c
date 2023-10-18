#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANZAHLN 49
#define ANZAHLZ 6

int main(void)
{
    srand(time(NULL));
    int array[ANZAHLN];
//  int gezogene_zahlen[ANZAHLZ];
    int zahl_ok = 1;

    for(int i = 0; i < ANZAHLN; i++)
    {
        array[i] = 0;
    }

//    for(int i = 0; i < 6; i++)
//    {
//        gezogene_zahlen[i] = 0;
//    }


    for(int i = 0; i < ANZAHLZ; i++)
    {
        do
        {
            int z = rand() % 50 + 1;

            if(array[z] == 0)
            {
                array[z] = 1;
                zahl_ok = 1;
            }
            else {
                zahl_ok = 0;
            }

        } while(zahl_ok == 0);
    }

    for(int j = 0; j < ANZAHLN; j++)
    {
        if(array[j] > 0)
        {
            printf(" %d ", j++);
        }
    }

    return 0;
}
