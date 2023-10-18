#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int max = atoi(argv[1]);
    int min = atoi(argv[1]);

    int pos_max = argc - (argc-1);
    int pos_min = argc - (argc-1);

    for(int i = 2; i < argc; i++){
        if(atoi(argv[i]) < min) {
           min = atoi(argv[i]);
           pos_min = i;
        }
        if(atoi(argv[i]) > max) {
            max = atoi(argv[i]);
            pos_max = i;
        }
    }

    if(min == max) {
        printf("Die Zahlen sind gleich!\n");
        return 1;
    }
    else{
        printf("Maximum ist %d an Stelle: %d, und Minimum ist %d an Stelle: %d.\n", max, pos_max, min, pos_min);
        return 0;
    }
}
