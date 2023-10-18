#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LEN 4096

const char *progName;

void errMsg(const char *operation, const char *fileName);

void errMsg(const char *operation, const char *fileName) {
    fprintf(stderr, "%s: error %s %s: %s\n", progName, operation, fileName, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[]) 
{   
    FILE *inFile, *outFile;
    progName = argv[0];

    char line[MAX_LINE_LEN + 2];
    const char *fromstr = argv[1];
    const char *tostr = argv[2];
    int len_fromstr = strlen(fromstr);

    if(len_fromstr == 0) {
        fprintf(stderr, "%s: Empty search string?\n", progName);
        exit(EXIT_FAILURE);
    }

    const char *inFileName, *outFileName;

    if(argc <= 2) {
        printf("%s: No words given!", progName);
    }
    if(argc > 5) {
        printf("%s: Too many words on Terminal!", progName);
    }

    if(argc == 3) {
        inFileName = "stdin";
        inFile = stdin;
        outFileName = "stdout";
        outFile = stdout;
    } else if (argc == 4) {
        inFileName = argv[3];
        if((inFile = fopen(inFileName, "r")) == NULL) {
            errMsg("opening (for reading)", inFileName);
        }
        outFileName = "stdout";
        outFile = stdout;
    } else if (argc == 5) {
        inFileName = argv[3];
        if((inFile = fopen(inFileName, "r")) == NULL) {
            errMsg("opening (for reading)", inFileName);
        }
        outFileName = argv[4];
        if((outFile = fopen(outFileName, "w")) == NULL) {
            errMsg("opening (for writing)", outFileName);
        }
    }

    while(fgets(line, sizeof(line), inFile)) {
        if(strchr(line, '\n') == NULL) {
            fprintf(stderr, "%s: error reading %s: line too long\n", progName, inFileName);
            exit(EXIT_FAILURE);
        }

        char *curPos;
        char *fromPos;
        for(curPos = line; (fromPos = strstr(curPos, fromstr)) != NULL; curPos = fromPos + len_fromstr) {
            *fromPos = '\0';
            
            if(fputs(curPos, outFile) == EOF) {
                errMsg("writing", outFileName);
            }
            if(fputs(tostr, outFile) == EOF) {
                errMsg("writing", outFileName);
            }
        }
        if(fputs(curPos, outFile) == EOF) {
            errMsg("writing", outFileName);
        }
    }

    if(ferror(inFile)) {
        errMsg("reading", inFileName);
    }

    if(fclose(inFile) == EOF) {
        errMsg("closing", inFileName);
    }
    if(fclose(outFile) == EOF) {
        errMsg("closing", outFileName);
    }

    exit(EXIT_SUCCESS);
}