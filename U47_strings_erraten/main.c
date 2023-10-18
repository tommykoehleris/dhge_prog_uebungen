#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 50

const char *words[] = {"schlagzeug", "eisenbahn", "text", "koehler", "tommy"};

int main(void) 
{
    srand(time(NULL));

    int arr_size = sizeof(words) / sizeof(words[0]);
    int word_number = rand() % arr_size;

    const char *word = words[word_number];

    int word_length = strlen(word);

    char ausgabe[MAX_LENGTH];

    for(int i = 0; i < word_length; ++i) {
        ausgabe[i] = '*';
    }
    ausgabe[word_length] = '\0';

    int versuche = 1;
    for(versuche = 1; ; ++versuche) {
        char eingabe[MAX_LENGTH];
        printf("%s\n Erraten Sie das Wort! Bitte einen Buchstaben oder das gesuchte Wort eingeben...", ausgabe);
        scanf("%s", eingabe);

        if(strlen(eingabe) == 1) {
            for(int i = 0; i < word_length; ++i) {
                if(word[i] == eingabe[0]) {
                    ausgabe[i] = word[i];
                }
            }
            if(strcmp(ausgabe, word) == 0) break;
        }
        else {    
            if(strcmp(eingabe, word) == 0) break;
            else printf("Das Wort war leider falsch!\n");
        }
    }
    printf("GEWONNEN! \"%s\" erraten in %d Versuchen.\n", word, versuche);
}