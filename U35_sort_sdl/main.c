#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "sdlinterf.h"

// Verz�gerungen (in Millisekunden) f�r die Grafik-Anzeige
// ... beim Start
#define START_MS 100
// ... am Ende (bevor das Fenster verschwindet)
#define ENDE_MS 2000
// ... bei jedem Vergleich
#define VERGL_MS 0
// ... bei jeder Vertauschung
#define TAUSCH_MS 0

// die Farbwwerte
const int farbe_normal[] = { 0, 255, 0 };     // normaler Balken
const int farbe_vergl[] = { 255, 255, 0 };    // zu vergleichender Balken
const int farbe_tausch[] = { 255, 0, 255 };   // zu vertauschender Balken
const int farbe_schwarz[] = { 0, 0, 0 };      // schwarz (zum Wegl�schen)

// Konstanten (in Pixeln) f�r das Grafik-Layout
// initialisiert in "main", benutzt in "balken"
// Breite eines Balkens
int breite;
// Eine H�hen-Einheit
int hoehe;
// Linker Rand = Startposition des ersten Balkens in X-Richtung
// (gleicher Rand links & rechts,
// damit die Balken im Fenster sch�n in der Mitte stehen)
int xstart;

// Z�hler f�r die Vergleiche und Vertauschungen
int vergl = 0;
int vertau = 0;

// Zeichne den Balken Nummer i in Farbe farbe
void balken(const int arr[], int i, const int farbe[])
{
  int xpos = xstart + i * breite;
  sdlDrawRectFromTo(xpos + 1, SDL_Y_SIZE - 1,
                    xpos + breite - 1, SDL_Y_SIZE - arr[i] * hoehe,
                    farbe[0], farbe[1], farbe[2]);
  sdlUpdate();
}

// Vergleiche mit farbiger Anzeige und Verz�gerung:
// Ist das Element an pos1 kleiner als das Element an pos2? (true / false)
// Da wir das Array mit lauter verschiedenen Elementen initialisieren,
// kommt "gleich" nicht vor!
bool kleiner(const int arr[], int pos1, int pos2)
{
  ++vergl;

  balken(arr, pos1, farbe_vergl);
  balken(arr, pos2, farbe_vergl);
  sdlMilliSleep(VERGL_MS);
  balken(arr, pos1, farbe_normal);
  balken(arr, pos2, farbe_normal);

  return (arr[pos1] < arr[pos2]);
}

// Vertausche die Elemente an pos1 und pos2 mit farbiger Anzeige und Verz�gerung
void tausche(int arr[], int pos1, int pos2)
{
  ++vertau;

  // zeichne die zu vertauschenden Balken f�rbig
  balken(arr, pos1, farbe_tausch);
  balken(arr, pos2, farbe_tausch);
  sdlMilliSleep(TAUSCH_MS);

  // zeichne den l�ngeren alten Balken schwarz,
  // weil sonst w�rde nach dem Tausch beim �berzeichnen mit dem k�rzeren Balken
  // oben ein Rest sichtbar bleiben!
  if (arr[pos1] > arr[pos2]) {
    balken(arr, pos1, farbe_schwarz);
  } else {
    balken(arr, pos2, farbe_schwarz);
  }

  // tausche
  int tmp = arr[pos1];
  arr[pos1] = arr[pos2];
  arr[pos2] = tmp;

  // zeichne die vertauschten Balken normal
  balken(arr, pos1, farbe_normal);
  balken(arr, pos2, farbe_normal);
}

// Bef�lle das Array zuf�llig mit den Zahlen 1 bis anzahl
// und zeige den Anfangszustand an
void fuelle(int arr[], int anzahl)
{
    srand(time(NULL));

    for(int i = 0; i < anzahl - 1; i++) {
        arr[i] = i + 1;
    }

    for(int j = 0; j < 3000; j++) {
        int x = rand() % anzahl;
        int y = rand() % anzahl;

        int hv = arr[x];
        arr[x] = arr[y];
        arr[y] = hv;
    }

    for(int i = 0; i < anzahl; i++) {
        balken(arr, i, farbe_normal);
    }
}

// sortiere das Array
// unter Verwendung von "kleiner" und "tausche"
void sort(int arr[], int anzahl)
{
    int array2[] = {301, 132, 57, 23, 10, 4, 1 };

    for(int j = 0; j <= 6; ++j) {
        int abst = array2[j];
        for(int pos = abst; pos < anzahl; ++pos) {
            for(int i = pos; (i >= abst) && kleiner(arr, i , i - abst); i -= abst) {
                tausche(arr, i, i - abst);
            }
        }
    }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    printf("Aufruf: %s anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int anzahl = atoi(argv[1]);
  if ((anzahl <= 0) || (anzahl > SDL_X_SIZE / 2) || (anzahl > SDL_Y_SIZE)) {
    printf("%s: Die Anzahl muss gr��er 0 sein "
          "und in das Grafikfenster passen\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Geometrie aus der Anzahl berechnen
  breite = SDL_X_SIZE / anzahl;
  hoehe = SDL_Y_SIZE / anzahl;
  xstart = (SDL_X_SIZE % anzahl) / 2;

  int array[anzahl];

  srand(time(NULL));

  sdlInit();
  sdlSetBlack();

  fuelle(array, anzahl);

  sdlMilliSleep(START_MS);

  sort(array, anzahl);

  printf("%d Vergleiche\n%d Vertauschungen\n", vergl, vertau);

  sdlMilliSleep(ENDE_MS);
  sdlExit();

  exit(EXIT_SUCCESS);
}


