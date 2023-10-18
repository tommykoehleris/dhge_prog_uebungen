#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLEVEL 100

const char *progName;

void sFile (FILE *f, const char *fileName);

void sFile (FILE *f, const char *fileName) {
    int c;
    int line = 1, col = 0;
    char close[MAXLEVEL];
    int current = -1;

    while((c = fgetc(f)) != EOF) {
        ++col;
        switch(c) {
            case '(':
            case '[':
            case '{':
                ++current;
                if(current == MAXLEVEL) {
                    printf("Array too small: %s, %d %d to deeply nested", fileName, line, col);
                    return;
                }
                close[current] = (c == '(') ? ')' : ((c == '[') ? ']' : '}');
                break;
            case ')':
            case ']':
            case '}':
                if(current == -1) {
                    printf("%s: %d %d: %c was never opened!\n", fileName, line, col, c);
                    return;
                } else if (c != close[current]) {
                    printf("%s: %d %d: Expected %c, found %c\n", fileName, line, col, close[current], c);
                    return;
                } else {
                    --current;
                }
                break;
            case '\n':
                ++line;
                col = 0;
                break;
            default: 
                break;
        }
    }

    if(ferror(f)) {
        fprintf(stderr, "%s: cannot read %s: %s\n", progName, fileName, strerror(errno));
        return;
    }
    if(current >= 0) {
        fprintf(stderr, "%s: %d %d: %c missing at end of file\n", fileName, line, col, c);
        return;
    }
}

int main(int argc, const char *argv[]) 
{
    progName = argv[0];

    if(argc == 1) {
        sFile(stdin, "stdin");
    } else {
        for(int i = 1; i < argc; ++i) {
            FILE *f = fopen(argv[i], "r");
            if(f == NULL) {
                fprintf(stderr, "%s: cannot open %s for reading: %s\n", progName, argv[i], strerror(errno));
                exit(EXIT_FAILURE);
            } else {
                sFile(f, argv[i]);
                fclose(f);
            }
        }
    }

    exit(EXIT_SUCCESS);
}