#include <stdlib.h>
#include <stdio.h>

const char *banane;

typedef struct eintrag {
    int z;
    int anz;
    struct eintrag *next;
} eintrag;

eintrag *neu(int z, eintrag *next_p);
eintrag *find(eintrag **head, int z);
void print(eintrag *head);

eintrag *neu(int z, eintrag *next_p) 
{
    eintrag *p = (eintrag *) (malloc(sizeof(eintrag)));
    if(p == NULL) {
        fprintf(stderr, "%s: ERROR: Not enough Memory to allocate.", banane);
        exit(EXIT_FAILURE);
    }
    
    p->z = z;
    p->anz = 0;
    p->next = next_p;
    return p;
}

eintrag *find(eintrag **head_p, int z)
{
    eintrag *head = *head_p;

    if((head == NULL) || (head->z>z)) {
        *head_p = neu(z, head);
        return *head_p;
    } else {
        
        for(eintrag *p = head; ;) {
            if(p->z == z) {
                return p;
            }

            eintrag *nach_p = p->next;
            if((nach_p == NULL) || (nach_p->z > z)) {
                p->next = neu(z, nach_p);
                return p->next;
            }

            p = nach_p; //um in der Liste weiterzugehen
        }
    }
}

void print(eintrag *head)
{
    for(eintrag *p = head; p != NULL; p = p->next) {
        printf("%d, Anzahl: %d\n", p->z, p->anz);
    }
    printf("\n");
}


int main(int argc, const char *argv[]) 
{   
    banane = argv[0];

    if(argc == 1) {
        fprintf(stderr, "%s: ERROR: Insert Numbers.", banane);
        exit(EXIT_FAILURE);
    }
    
    eintrag *head = NULL;

    for(int i = 1; i < argc; ++i) {
        int z = atoi(argv[i]);

        eintrag *p = find(&head, z);
        ++(p->anz);

        print(head);
    }

    exit(EXIT_SUCCESS);
}