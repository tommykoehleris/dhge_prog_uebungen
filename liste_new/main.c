#include <stdlib.h>
#include <stdio.h>

struct element{
    int zahl;
    int anz;
    struct element *next;
};

typedef struct element element;

element *neu(int zahl, element *next);
element *find(element **head_p, int zahl); 
void print(element *head); 

element *neu(int zahl, element *next) 
{
    element *p = (element *) (malloc(sizeof(element)));
    if(p == NULL) {
        fprintf(stderr, "[ERROR]: Allocating Memory.");
        exit(EXIT_FAILURE);
    }

    p->anz = 0;
    p->next = next;
    p->zahl = zahl;

    return p;
}

element *find(element **head_p, int zahl) 
{
    element *head = *head_p;
    if((head == NULL) || (head->zahl > zahl)) {
        *head_p = neu(zahl, head);
        return *head_p;
    } else {
        for(element *p = head; ;) {
            if(p->zahl == zahl) {
                return p;
            }

            element *next_p = p->next;
            if((next_p == NULL) || (next_p->zahl > zahl)) {
                p->next = neu(zahl, next_p);
                return p->next;
            }
            
            p = next_p;
        }   
    }
}

void print(element *head) 
{
    for(element *p = head; p != NULL; p = p->next) {
        printf("Zahl: %d // Anzahl: %d\n", p->zahl, p->anz);
    }
    printf("\n");
}

int main(int argc, const char *argv[]) 
{
    element *head = NULL;
    
    for(int i = 1; i < argc; ++i) {
        int zahl = atoi(argv[i]);

        element *p = find(&head, zahl);
        ++(p->anz);

        print(head);
    }

    exit(EXIT_SUCCESS);
}