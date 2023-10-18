#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char name[32];
    double gewicht;
    double wert;
    bool gerade_dabei;
    bool optimal_dabei;
    double gewichts_wert;
} gegenstand;

gegenstand liste[] = {
    {"Apfel", 10, 5, false, false, 0 },
    {"Müsliriegel", 2.5, 25, false, false, 0 },
    {"Goldring", 0.5, 1666, false, false, 0 },
    {"Schleppdepp", 70, 499.99, false, false, 0 },
    {"Pass", 0.5, 60, false, false, 0 },
    {"Geldbörse", 5, 123.27, false, false, 0 },
    {"Kamera", 49.5, 459.99, false, false, 0 },
    {"Brille", 13, 260.50, false, false, 0 },
    {"Saft", 30, 30, false, false, 0 },
    {"Pullover", 12, 20, false, false, 0 },
    {"Regenmantel", 3.5, 40, false, false, 0 },
    {"Messer", 10, 50, false, false, 0 },
    {"Taschentuch", 0.1, 0.5, false, false, 0 },
    {"Klopapier", 0.5, 5, false, false, 0 },
    {"Banane", 5, 10, false, false, 0 },
    {"Karte", 1.5, 20, false, false, 0 },
    {"Sonnencreme", 7.5, 40, false, false, 0 }
};

const int anzahl_liste = sizeof(liste)/sizeof(liste[0]);
double best_wert = 0;

int aufruf = 0;

void gltg_beladung (double wert);
void probieren(int i, double platz, double wert);

int vergleiche(const void *p1, const void *p2) {
    const gegenstand *a = (const gegenstand *)p1;
    const gegenstand *b = (const gegenstand *)p2;

    if(a->gewichts_wert < b->gewichts_wert) {
        return 1;
    }
    if(a->gewichts_wert > b->gewichts_wert) {
        return -1;
    }

    return 0;
}

void gltg_beladung(double wert) {
    if(wert > best_wert) {
        best_wert = wert;
        for(int j = 0; j < anzahl_liste; ++j) {
            liste[j].optimal_dabei = liste[j].gerade_dabei;
        }
    }
}

void probieren(int i, double platz, double wert) {
    
    ++aufruf;
    if(i == anzahl_liste) {
        gltg_beladung(wert);
        return;
    }

    gegenstand *g = &(liste[i]); //zeiger auf gegenstand

    if(wert + platz * g->gewichts_wert <= best_wert) {
        return;
    }

    if(g->gewicht <= platz) {
        g->gerade_dabei = true;
        probieren(i + 1, platz - g->gewicht, wert + g->wert);
    }

    g->gerade_dabei = false;
    probieren(i + 1, platz, wert);
}

int main(int argc, const char *argv[]) 
{
    double max_gewicht;
    if((argc != 2) || ((max_gewicht = (atof(argv[1]))) <= 0)) {
        fprintf(stderr, "%s: Fehlerhafte Eingabe", argv[0]);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < anzahl_liste; ++i) {
        liste[i].gewichts_wert = liste[i].wert/liste[i].gewicht;
    }

    qsort(liste, anzahl_liste,sizeof(gegenstand), vergleiche);

    probieren(0, max_gewicht, 0);

    double gesamt_gewicht;
    double gesamt_wert = best_wert;

    for(int i = 0; i < anzahl_liste; ++i) {
        if (liste[i].optimal_dabei) {
            printf("%s: Gewicht %9.2f, Wert %9.2f\n", liste[i].name, liste[i].gewicht, liste[i].wert);
            gesamt_gewicht += liste[i].gewicht;
        }
    }

    printf("\nEndsumme: Gewicht %9.2f, Wert %9.2f\n", gesamt_gewicht, gesamt_wert);
    printf("%d Aufrufe", aufruf);

    exit(EXIT_SUCCESS);
}