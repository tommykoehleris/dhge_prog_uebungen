#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  // SDL_X_SIZE ist die horizontale Fenstergr��e in Pixeln
  // SDL_Y_SIZE ist die vertikale Fenstergr��e in Pixeln
  const int mitteX = 400;
  int mitteY = 40;
  int halbX = 20;


  sdlInit();       // mach das Grafik-Fenster auf
  sdlSetBlack();   // mach alle Pixel schwarz

  sdlDrawCirc(mitteX, mitteY, 50, 30, 128, 64,0);

  for (int i = 0; halbX + i <= 270; i += 25)
  {
    sdlDrawCirc(mitteX, mitteY + i + i, halbX + i, 30, 0, 255, 0);
//    mitteY += 50;
//    halbX += 25;

//    if(mitteY == 540)
//    {
//        break;
//    }
//    sdlUpdate();
//    sdlMilliSleep(50);
  }


  sdlUpdate();
  sdlMilliSleep(6000);   // warte wieder 3 Sekunden
  sdlExit();             // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}
