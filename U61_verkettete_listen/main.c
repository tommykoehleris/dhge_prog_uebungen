#include <stdio.h>
#include <stdlib.h>

struct eintrag {
    int zahl;
    int anz;
    struct eintrag *next;
};

typedef struct eintrag eintrag;

eintrag *neu(int z, eintrag *n);
eintrag *find(eintrag **head, int z);
void print(eintrag *head, int durchlauf);

eintrag *neu(int z, eintrag *n) {
    
    eintrag *p = (eintrag *) (malloc(sizeof(eintrag)));
    if(p == NULL) {
        fprintf(stderr, "Memory allocation error...\n");
        exit(EXIT_FAILURE);
    }
    p->zahl = z;
    p->anz = 0;
    p->next = n;
    return p;
}

eintrag *find(eintrag **head_p, int z) {
    eintrag *head = *head_p;
    if((head == NULL) || (head->zahl > z)) {
        *head_p = neu(z, head);
        return *head_p;
    } else {
        for (eintrag *p = head; ; ) {   
            if (p->zahl == z) {
                return p;
            }
            eintrag *next_p = p->next;
            if((next_p == NULL) || (next_p->zahl > z)) {
                p->next = neu(z, next_p);
                return p->next;
            }
            p = next_p;
        }
    }
}

void print(eintrag *head, int durchlauf) {
    for(eintrag *p = head; p != NULL; p = p->next) {
        printf("%d: Anz:%d ", p->zahl, p->anz);
    }
    printf("\nDas war Durchlauf %d...\n\n", durchlauf);
}

int main(int argc, const char *argv[]) {
    eintrag *head = NULL;
    
    int durchlauf;
    for(durchlauf = 1; durchlauf < argc; ++durchlauf) {
        eintrag *p = find(&head, atoi(argv[durchlauf]));
        
        ++(p->anz);
        print(head, durchlauf);
    }

    exit(EXIT_SUCCESS);
}

