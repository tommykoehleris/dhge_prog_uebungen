#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdlinterf.h"

int leben[SDL_X_SIZE][SDL_Y_SIZE];
int nachbarn[SDL_X_SIZE][SDL_Y_SIZE];

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    //Lebens-Schleife
    for(int i = 0; i < SDL_Y_SIZE; i++)
    {
        for(int j = 0; j < SDL_X_SIZE; j++)
        {
            int lebendig = rand() % 2;
            leben[j][i] = lebendig;
        }
    }

    for(int i = 0; i < SDL_Y_SIZE; i++)
    {
        leben[0][i] = 0;
        leben[SDL_X_SIZE-1][i] = 0;
    }

    for(int i = 0; i < SDL_X_SIZE; i++)
    {
        leben[i][0] = 0;
        leben[i][SDL_Y_SIZE-1] = 0;
    }

    //Generationen-Schleife

    sdlInit();

    for (;;)
    {
   sdlSetBlack();

        for(int i = 1; i < SDL_X_SIZE-1; i++)
        {
            for(int j = 1; j < SDL_Y_SIZE-1; j++)
            {
                nachbarn[i][j] =
                    leben[i-1][j] + leben[i+1][j] +
                    leben[i][j+1] + leben[i][j-1] +
                    leben[i-1][j-1] + leben[i+1][j-1] +
                    leben[i-1][j+1] + leben[i+1][j+1];
            }
        }

        for(int i = 1; i < SDL_X_SIZE-1; i++)
        {
            for(int j = 1; j < SDL_Y_SIZE-1; j++)
            {
                int m_faktor = 1/atof(argv[1]);

                if ((leben[i][j] == 1) && ((nachbarn[i][j] == 2) || (nachbarn[i][j] == 3)))
                {
                    sdlDrawPoint(i,j,255,0,0);
                }
                else if ((nachbarn[i][j] == 3) || ((m_faktor > 0) && (rand() % m_faktor == 0)))
                {
                    leben[i][j] = 1;
                    sdlDrawPoint(i,j,255,255,0);
                }
                else
                {
                    leben[i][j] = 0;
                }
            }
        }
        sdlUpdate();

    }

}