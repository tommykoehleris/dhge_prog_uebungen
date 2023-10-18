#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256

struct zeile {
    const char *filename;
    int line_nr;
    const char *text;
    struct zeile *next;
};

struct liste {
    struct zeile *head;
    struct zeile *tail;
};

typedef struct zeile zeile;
typedef struct liste liste;

void save(liste zeilen[], const char *filename, int line_nr, const char *text);
void file_work(liste zeilen[], const char *filename);
void print(liste zeilen[]);

void save(liste zeilen[], const char *filename, int line_nr, const char *text) {
    zeile *n = (zeile *) (malloc(sizeof(zeile)));
    
    n->text = strdup(text);
    n->filename = filename;
    n->line_nr = line_nr;
    n->next = NULL;

    size_t len = strlen(text);
    if(zeilen[len].head == NULL) {
        zeilen[len].head = n;
    } else {
        zeilen[len].tail->next = n;
    }
    zeilen[len].tail = n;
}

void file_work(liste zeilen[], const char *filename) {
    FILE *f;
    char line[MAX_LINE_LEN];
    
    if((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[ERROR]: Opening File %s", filename);
        exit(EXIT_FAILURE);
    }

    int line_nr;
    for(line_nr = 1; fgets(line, 256, f); ++line_nr) {
        if(strchr(line, '\n') == NULL) {
            fprintf(stderr, "[ERROR]: Line too long (%s:%d).\n", filename, line_nr);
            exit(EXIT_FAILURE);
        }

        save(zeilen, filename, line_nr, line);
    }

    fclose(f);
}

void print(liste zeilen[]) {
    for(int i = 0; i < MAX_LINE_LEN; ++i) {
        for(zeile *p = zeilen[i].head; p != NULL; p = p->next) {
            printf("%s: %d: %s", p->filename, p->line_nr, p->text);
        }
    }
}

int main(int argc, const char *argv[])
{
    liste zeilen[MAX_LINE_LEN];
    
    for(int i = 0; i < MAX_LINE_LEN; ++i) {
        zeilen[i].head = zeilen[i].tail = NULL;
    }

    if(argc == 1) {
        fprintf(stderr, "[ERROR]: No Arguments!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; ++i) {
        file_work(zeilen, argv[i]);
    }

    print(zeilen);

    exit(EXIT_SUCCESS);
}



