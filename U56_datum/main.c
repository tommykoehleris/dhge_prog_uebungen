#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *wochentage[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};

int main(int argc, const char *argv[])
{
    struct tm input = {
        0, 0, 12, 
        atoi(argv[1]), atoi(argv[2]) - 1, atoi(argv[3]) - 1900, 
        0, 0, -1
    };

    time_t seconds = mktime(&input);

    if(seconds == -1) {
        printf("Zeit ausserhalb des berechenbaren Bereichs!\n");
        exit(EXIT_FAILURE);
    }

    struct tm *output = localtime(&seconds);

        printf("Der %d.%d. des Jahres %d, ist ein %s (%d. Tag des Jahres).\n",
            output->tm_mday, output->tm_mon + 1, output->tm_year + 1900, wochentage[output->tm_wday], output->tm_yday + 1);
        
        return 0;
}