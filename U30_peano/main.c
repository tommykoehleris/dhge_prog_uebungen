#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sdlinterf.h"

int xPos, yPos; // aktuelle x- und y-Position, in Pixel (0/0 = links oben)
int richtung;   // aktuelle Richtung, wichtig ist der Rest bei Division durch 4:
                // 0 ... rechts runter (+x+y), 1 ... rechts rauf (+x-y),
                // 2 ... links rauf (-x-y), 3 ... links runter (-x+y)
int schritt;    // Wie viele Pixel ist ein Teilstrich in x- und y-Richtung lang?
int verz;       // Verz�gerung nach jedem Schritt, in Millisekunden

// Farb-Tabelle
const int R[] = {   0,  85, 170, 255, 170,  85,   0,   0,   0 };
const int G[] = { 255, 170,  85,   0,   0,   0,   0,  85, 170 };
const int B[] = {   0,   0,   0,   0,  85, 170, 255, 170,  85 };

// Hier fehlt die Funktion zeichne
// Zeichne das Muster mit Rekursion der Tiefe "tiefe" f�r jeden Teilstrich
void zeichne(int tiefe);

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    printf("Aufruf: %s rekursionstiefe\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Rekursionstiefe
  int tiefe = atoi(argv[1]);
  if (tiefe <= 0) {
    printf("%s: Rekursionstiefe muss > 0 sein!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Berechne schritt = L�nge eines Teilstriches
  // Entspricht k�rzerer Fenster-Seite pro Rekursionsebene ein mal gedrittelt
  int seite = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 1;
  int potenz = pow(3, tiefe);
  schritt = seite / potenz;
  if (schritt == 0) {
    printf("%s: Rekursionstiefe ist zu hoch!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Tats�chliche Seitenl�nge der Grafik
  seite = schritt * potenz;
  // Anfangsposition = linke obere Ecke so berechnen,
  // dass die Grafik im Fenster sch�n zentriert ist
  xPos = (SDL_X_SIZE - seite) / 2;
  yPos = (SDL_Y_SIZE - seite) / 2;

  // absoluter Wert von richtung ist egal
  // nur Rest durch 4 ist wichtig, muss am Anfang 0 = "rechts runter" sein
  // aber richtung darf nicht negativ werden ==> mit gro�er Zahl anfangen!
  richtung = 1000;
  // je gr��er die Tiefe, umso mehr Teilstriche
  // ==> umso k�rzere Verzogerung pro einzelnem Teilstrich
  verz = 1500 / pow(5, tiefe);

  sdlInit();
  zeichne(tiefe);
  // "ewig" anzeigen, dabei alle 100 ms auf "beenden" pr�fen
  for (;;) { sdlMilliSleep(100); }
  sdlExit();

  exit(EXIT_SUCCESS);
}

void zeichne(int tiefe) {
  int xPos_alt = xPos;
  int yPos_alt = yPos;

  if(tiefe == 0) {
    switch(richtung) {
      case 0: 
        xPos = xPos_alt + schritt;
        yPos = yPos_alt + schritt;

        sdlDrawLine(xPos_alt, yPos_alt, xPos, yPos, R[richtung % 9], G[richtung % 9], B[richtung % 9]);
        break;
      case 1:
        xPos = xPos_alt + schritt;
        yPos = yPos_alt - schritt;

        sdlDrawLine(xPos_alt, yPos_alt, xPos, yPos, R[richtung % 9], G[richtung % 9], B[richtung % 9]);
        break;
      
      case 2:
        xPos = xPos_alt - schritt;
        yPos = yPos_alt - schritt;

        sdlDrawLine(xPos_alt, yPos_alt, xPos, yPos, R[richtung % 9], G[richtung % 9], B[richtung % 9]);
        break;

      case 3:
        xPos = xPos_alt - schritt;
        yPos = yPos_alt + schritt;

        sdlDrawLine(xPos_alt, yPos_alt, xPos, yPos, R[richtung % 9], G[richtung % 9], B[richtung % 9]);
        break;
    }
  }
  else {
    --tiefe;
    
    zeichne(tiefe);

  }
  sdlUpdate();
  sdlMilliSleep(verz);
}
