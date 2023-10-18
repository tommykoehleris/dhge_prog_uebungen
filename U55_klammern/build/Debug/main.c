#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

const char *progName;

void errMsg(const char *operation, const char *fileName);

void errMsg(const char *operation, const char *fileName) 
{
    fprintf(stderr, "%s: error: %s %s: %s\n", progName, operation, fileName, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[]) 
{
    progName = argv[0];

    FILE *inputFile, *outputFile;
    const char *inFileName, *outFileName;

    if(argc != 3) {
        fprintf(stderr, "Aufruf: %s infile outfile\n", progName);
        exit(EXIT_FAILURE);
    }

    inFileName = argv[1];
    outFileName = argv[2];

    if((inputFile = fopen(inFileName, "r")) == NULL) {
        errMsg("opening (reading file)", inFileName);
    }

    if((outputFile = fopen(outFileName, "w")) == NULL) {
        errMsg("opening (writing file)", outFileName);
    }

    int c;
    int len = 0;
    int max = 0;
    int del = 0;

    while((c = fgetc(inputFile)) != EOF) {
        if(isspace(c)) {
            if(len == 0) {
                if(fputc(c, outputFile) == EOF) {
                    errMsg("writing in outputFile", outFileName);
                }
            } else {
                ++del;
            }
            ++len;
        } else {
            if(fputc(c, outputFile) == EOF) {
                errMsg("writing into outputFile", outFileName);
            }
            if(len > max) {
                max = len;
            }
            len = 0;
        }
    }

    if(len > max) {     //falls Datei nur Leerraum enthielt
        max = len;
    }

    if(ferror(inputFile)) {
        errMsg("reading", inFileName);
    }

    if(fclose(inputFile) == EOF) {
        errMsg("closing", inFileName);
    }

    if(fclose(outputFile) == EOF) {
        errMsg("closing", outFileName);
    }

    fprintf(stderr, "%s: %d chars deleted, longest: %d\n", inFileName, del, max);

    exit(EXIT_SUCCESS);
}