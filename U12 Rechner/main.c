#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[])
{
    double ergebnis = atof(argv[1]);

    if(argc % 2 != 0)
        {
            printf("Falsche Anzahl an Zahlen auf der Befehlszeile.\n");

        }

    for(int i = 2; i < argc; i += 2)
    {
        double zahl_neu = atof(argv[i + 1]);

        switch (argv[i][0])
        {
        case 'x':
            ergebnis *= zahl_neu;
            break;
        case '+':
            ergebnis += zahl_neu;
            break;
        case '-':
            ergebnis -= zahl_neu;
            break;
        case '/':
            if (zahl_neu == 0)
            {
                printf("%s: Division durch 0!\n", argv[0]);
                return 1;
            }
            ergebnis /= zahl_neu;
            break;

        }
    }

    printf("%g\n", ergebnis);

    return 0;
}

