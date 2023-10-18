#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool match(const char text[], const char wildcard[])
{
    for(int i = 0; ; ++i) {
        if(wildcard[i] == '\0') {
            if(text[i] == '\0') return true;
            else return false;
        }
        else if(wildcard[i] == '@') {
            for(int j = i; ; ++j) {
                if(match(&text[j], &wildcard[i + 1])) return true;
                if(text[j] == '\0') return false;
            }
        }
        else if(text[i] == '\0') {
            return false;
        }
        else if(wildcard[i] == '%') {
        }
        else {
            if(wildcard[i] != text[i]) {
                return false;
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    if(argc != 3) {
        printf("Fehler bei Eingabe!");
    }
        
    printf("%s\n", match(argv[1], argv[2]) ? "match" : "failed");
}