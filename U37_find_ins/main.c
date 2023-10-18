#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 6

int find(const int array[], int anz, int search_zahl);
int insert(int arrary[], int *anz_p, int size, int ins_zahl);
int insertNoDup(int array[], int *anz_p, int size, int ins_zahl);

int find(const int array[], int anz, int search_zahl) 
{
    for(int i = 0; i < anz; ++i) {
        if(array[i] == search_zahl) {
            return i;
        }
    }
    return -1;    
}

int insert(int array[], int *anz_p, int size, int ins_zahl) 
{
    int lücke;
    for(lücke = *anz_p; (lücke > 0) && (array[lücke - 1] > ins_zahl); --lücke) {
        array[lücke] = array[lücke - 1];
    }
    array[lücke] = ins_zahl;
    ++(*anz_p);

    if((*anz_p > size) || *anz_p < 0) {
        return -1;
    }
    
    return lücke;
}

int insertNoDup(int array[], int *anz_p, int size, int ins_zahl) 
{
    if((find(array, size, ins_zahl)) >= 0) {
        return -1;
    }
    return insert(array, anz_p, size, ins_zahl);
}

int main(int argc, const char *argv[]) 
{   
    int zahlen[ARR_SIZE];
    int anzahl_elem = 0; //am Anfang leeres Array

    if(argc == 1) {
        printf("!!!Error: No numbers to insert, please type in!!!\n");
    }

    for(int i = 1; i < argc; ++i) {
        int z = atoi(argv[i]);
        int pos = insertNoDup(zahlen, &anzahl_elem, ARR_SIZE, z);

        if(pos == -1) {
            fprintf(stderr, "\n!!!%s: cant insert %d!!!\n", argv[0], z);
            exit(EXIT_SUCCESS);
        } else {
            printf("%d inserted at position: %d\n", z, pos);
        }
    }
    printf("\n");

    for(int j = 0; j < anzahl_elem; ++j) {
        printf("%d ", zahlen[j]);
    }   

    printf("\nInfo: aktuell noch freier Platz im Array: %d\n\n", (ARR_SIZE-anzahl_elem));

    exit(EXIT_SUCCESS);
}