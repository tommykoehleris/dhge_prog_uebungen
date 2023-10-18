#include <stdio.h>
#include <stdlib.h>

#define ANZAHL = 100000

int main(void)
{
    srand(time(NULL));
    int anz_sechser = 0;
    int zahl = 0;
    int anzahl_sechser_insg = 0;
    int versuche = 0;

    for(int durchlauf = 1; durchlauf < 100000; durchlauf++) {

        do {
            zahl = rand() % 6 + 1;
            //printf("Das war der %d. Wurf, es war eine %d!\n", durchlauf, zahl);

            if(zahl == 6) {
                ++anz_sechser;
                anzahl_sechser_insg++;
            }
        } while(anz_sechser < 2);
    }

    printf("Es wurden %d Mal zwei Sechser nacheinander geworfen!\n", anzahl_sechser_insg);
    //printf("Das war der %d. Wurf, es war noch eine 6!\n\n", i);
    //printf("Es wurden zwei 6er hintereinander geworfen.\n");
    return 0;
}
