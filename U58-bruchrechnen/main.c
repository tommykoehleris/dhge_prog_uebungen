#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct bruch{
    int z;
    int n;
};

typedef struct bruch bruch;

int ggT(int a, int b);
void kuerzen(bruch *b);
bruch Plus(bruch l, bruch r);
bruch Minus(bruch l, bruch r);
bruch Mal(bruch l, bruch r);
bruch Geteilt(bruch l, bruch r);
void Ausgabe(bruch a);
bruch Eingabe(const char *string);

int ggT(int a, int b) {

    a = abs(a);
    b = abs(b);

    while(b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

void kuerzen(bruch *b) {
    if(b->n == 0) {
        printf("Nenner ist 0!\n");
        exit(EXIT_FAILURE);
    }

    if(b->n < 0) {
        b->z = -b->z;
        b->n = b->n;
    }

    int g = ggT(b->z, b->n);
    b->z /= g;
    b->n /= g;
}

void Ausgabe(bruch a) {
    if(a.n != 1){
        printf("%d/%d\n", a.z, a.n);
    } else {
        printf("%d\n", a.z);
    }
}

bruch Plus(bruch l, bruch r) {
    bruch ergeb;
    ergeb.z = l.z * r.n + r.z * l.n;
    ergeb.n = l.n * r.n;
    kuerzen(&ergeb);
    return ergeb;
}

bruch Minus(bruch l, bruch r) {
    bruch ergeb;
    ergeb.z = l.z * r.n - r.z * l.n;
    ergeb.n = l.n * r.n;
    kuerzen(&ergeb);
    return ergeb;
}

bruch Mal(bruch l, bruch r) {
    bruch ergeb;
    ergeb.z = l.z * r.z;
    ergeb.n = l.n * r.n;
    kuerzen(&ergeb);
    return ergeb;
}

bruch Geteilt(bruch l, bruch r) {
    bruch ergeb;
    ergeb.z = l.z * r.n;
    ergeb.n = l.n * r.z;
    kuerzen(&ergeb);
    return ergeb;
}

bruch Eingabe(const char *str) {
    bruch ergeb;
    ergeb.z = atoi(str);
    const char *p = strchr(str, '/');
    if(p == NULL) {
        ergeb.n = 1;
    } else {
        ergeb.n = atoi(p + 1);
    }
    kuerzen(&ergeb);
    return ergeb;
}

int main(int argc, const char *argv[])
{
    bruch ergebnis = Eingabe(argv[1]);

    if(argc % 2 != 0)
        {
            printf("Falsche Anzahl an Zahlen auf der Befehlszeile.\n");
        }

    for(int i = 2; i < argc; i += 2)
    {
        bruch zahl_neu = Eingabe(argv[i + 1]);

        switch (argv[i][0])
        {
        case 'x':
            ergebnis = Mal(ergebnis, zahl_neu);
            break;
        case '+':
            ergebnis = Plus(ergebnis, zahl_neu);
            break;
        case '-':
            ergebnis = Minus(ergebnis,zahl_neu);
            break;
        case '/':
            ergebnis = Geteilt(ergebnis, zahl_neu);
            break;
        }
    }

    Ausgabe(ergebnis);

    return 0;
}
