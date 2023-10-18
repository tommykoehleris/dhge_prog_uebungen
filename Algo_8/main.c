#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LEN 256

const char *progname;

typedef struct line {
    const char *filename;
    int line_num;
    const char *line_txt;
    struct line *next;
} list_ele;

typedef struct list{
    list_ele *head;
    list_ele *tail;
} list;

void list_logic(list lines[], const char *filename, int line_num, const char *line_txt);
void file_read(list lines[], const char *filename);

void list_logic(list lines[], const char *filename, int line_num, const char *text) 
{
    list_ele *p = (malloc(sizeof(list_ele)));
    if(p == NULL) {
        fprintf(stderr, "%s: ERROR: Out of Memory!", progname);
        exit(EXIT_FAILURE);
    } 

    p->line_txt = strdup(text);
    if(p->line_txt == NULL) {
        fprintf(stderr, "%s: ERROR: Saving Line-Text!", progname);
        exit(EXIT_FAILURE);
    }

    p->filename = filename;
    p->line_num = line_num;
    p->next = NULL;

    size_t line_len = strlen(text);
    if(lines[line_len].head == NULL) {
        lines[line_len].head = p;
    } else {
        lines[line_len].tail->next = p;
    }
    lines[line_len].tail = p;  
}

void file_read(list lines[], const char *filename) 
{
    char line[MAX_LINE_LEN];

    FILE *f;

    if((f = fopen(filename,"r")) == NULL) {
        fprintf(stderr, "%s: ERROR: Opening File %s.", progname, filename);
        exit(EXIT_FAILURE);
    }

    for(int line_nr = 1; fgets(line, sizeof(line), f); line_nr++) {
        if((strchr(line, '\n') == NULL) || (sizeof(line) >= MAX_LINE_LEN)) {
            fprintf(stderr, "%s: ERROR: Line %d too long.", progname, line_nr);
            exit(EXIT_FAILURE);
        }

        list_logic(lines, filename, line_nr, line);

        if(ferror(f)) {
            fprintf(stderr, "%s: ERROR: Cant read %s... %s", progname, filename, strerror(errno));
            exit(EXIT_FAILURE);
        } 
    }
    fclose(f);
}

void output(list lines[]) 
{
    for(int i = 0; i < MAX_LINE_LEN; i++) {
        for(list_ele *p = lines[i].head; p != NULL; p = p->next) {
            printf("%s: %d: %s", p->filename, p->line_num, p->line_txt);
        }
    }
}

int main(int argc, const char *argv[]) 
{
    progname = argv[0];

    list list_array[MAX_LINE_LEN];

    for(int i = 0; i <= MAX_LINE_LEN; ++i) {
        list_array[i].head = list_array[i].tail = NULL;
    }

    if(argc <= 1) {
        fprintf(stderr, "%s: ERROR: Input Filename.", progname);
        exit(EXIT_FAILURE);
    }
    for(int j = 0; j <= argc; ++j) {
        file_read(list_array, argv[j]);
    }

    output(list_array);

    exit(EXIT_SUCCESS);
}