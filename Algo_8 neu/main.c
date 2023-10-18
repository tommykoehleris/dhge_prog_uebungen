#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 256

struct line{
    const char *filename;
    int line_nr;
    const char *text;
    struct line *next;
};

typedef struct line line;

struct list{
    line *head;
    line *tail;
};

typedef struct list list;

void save_line(list listen[], const char *filename, int line_nr, const char *text);
void work_on_file(list listen[], const char *filename);
void output(list listen[]);

void save_line(list listen[], const char *filename, int line_nr, const char *text)
{
    line *p = (line *) (malloc(sizeof(line)));
    if (p == NULL) 
    {
        fprintf(stderr, "[ERROR]: Not enough Memory to allocate.");
        exit(EXIT_FAILURE);
    }

    p->text = strdup(text);
    p->filename = filename;
    p->line_nr = line_nr;
    p->next = NULL;

    size_t i = strlen(text);
    if (listen[i].head == NULL) 
    {
        listen[i].head = p;
    } else {
        listen[i].tail->next = p;
    }

    listen[i].tail = p;
}

void work_on_file(list listen[], const char *filename)
{
    FILE *f;
    char line[MAX_LINE_LEN];

    if((f = fopen(filename, "r")) == NULL) 
    {
        fprintf(stderr, "[ERROR]: Opening File %s", filename);
        exit(EXIT_FAILURE);
    }

    for(int line_nr = 1; fgets(line, sizeof(line), f); ++line_nr)
    {
        save_line(listen, filename, line_nr, line);
    }

    fclose(f);
}

void output(list listen[])
{
    for(int i = 0; i < MAX_LINE_LEN; ++i) 
    {
        for(line *p = listen[i].head; p != NULL; p = p->next)
        {
            printf("%s: %d: %s", p->filename, p->line_nr, p->text);
        }
    }
}

int main (int argc, const char *argv[])
{
    list listen[MAX_LINE_LEN];

    for (int i = 0; i <= MAX_LINE_LEN; ++i)
    {
        listen[i].head = listen[i].tail = NULL;
    }

    if (argc != 2)
    {
        fprintf(stderr, "[ERROR]: Enter Filename.");
        exit(EXIT_FAILURE);
    }

    for (int j = 1; j < argc; ++j)
    {
        work_on_file(listen, argv[j]);
    }

    output(listen);

    exit(EXIT_SUCCESS);
}