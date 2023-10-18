#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 8

int find(const int array[], int anzahl, int zahl);
int insert(int array[], int *anzahlP, int size, int zahl);
int insertNoDup(int array[], int *anzahlP, int size, int zahl);

int find(const int array[], int anzahl, int zahl)
{
    for(int i = 0; i < anzahl; ++i) {
        if(array[i] == zahl) {
            return i;
        } 
    }
    return -1;
}

int insert(int array[], int *anzahlP, int size, int zahl) 
{
    if((*anzahlP < 0) || (*anzahlP >= size)) {
        return -1;
    }

    int loch;
    for(loch = *anzahlP; (loch > 0) && (array[loch - 1] > zahl); --loch) {
        array[loch] = array[loch - 1];
    }   

    array[loch] = zahl;
    ++(*anzahlP);
    return loch;
}

int insertNoDup(int array[], int *anzahlP, int size, int zahl) 
{
    if(find(array, *anzahlP, zahl) != -1) {
        return -1;
    }

    return insert(array, anzahlP, size, zahl);
}

int main(int argc, const char *argv[])
{
    int array[ARR_SIZE];
    int anzahl = 0;

    for(int i = 1; i < argc; ++i) {
        int zahl = atoi(argv[i]);
        int pos = insertNoDup(array, &anzahl, ARR_SIZE, zahl);

        if(pos == -1) {
            printf("[ERROR]: %d not inserted...\n", zahl);
        } else {
            printf("[IN]: %d inserted at pos: %d!\n", zahl, pos);
        }
    }

    putchar('\n');
    for(int i = 0; i < anzahl; ++i) {
        printf("Position: %d // Zahl:%d\n", i, array[i]);
    }
    printf("Aktuell belegt: %d", anzahl);

    exit(EXIT_SUCCESS);
}

