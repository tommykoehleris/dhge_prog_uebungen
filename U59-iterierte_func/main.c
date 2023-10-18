#include <stdlib.h>
#include <time.h>
#include "sdlinterf.h"

typedef struct {
    double x;
    double y;
} punkt;

typedef struct {
    double wert;
    double min_wert;
    double max_wert;
    double schritt;
}koeff;

typedef struct {
    int proz_rot, proz_gruen, proz_blau, dazu_rot, dazu_gruen, dazu_blau;
} farbinfo;

#include "spirale.h"

punkt p [ANZAHL];

int main(void)
{
    srand(time(NULL));

    sdlInit();

    double xmin, ymin, xmax, ymax;
    xmin = ymin = 1e300;
    xmax = ymax = -1e300;

    p[0].x = 0;
    p[0].y = 0;

    for(int i = 1; i < (ANZAHL - 1); ++i) {
        int n;
        int r = rand() % 100;
        for(n = 0; r >= prozent[n]; ++n) {}

        p[i].x = c[0][n].wert * p[i - 1].x +
                c[1][n].wert * p[i - 1].y +
                c[2][n].wert;
        p[i].y = c[3][n].wert * p[i - 1].x +
                c[4][n].wert * p[i - 1].y +
                c[5][n].wert;

        if(i >= ERSTER) {
            if(p[i].x < xmin) xmin = p[i].x;
            if(p[i].x > xmax) xmax = p[i].x;
            if(p[i].y < ymin) ymin = p[i].y;
            if(p[i].y > ymax) ymax = p[i].y;
        }
    }

    for(int i = ERSTER; i < ANZAHL; ++i) {
        sdlDrawPoint(((p[i].x - xmin) / (xmax - xmin)) * (SDL_X_SIZE - 1),
                 (1 - (p[i].y - ymin) / (ymax - ymin)) * (SDL_Y_SIZE - 1),
                 0, 255, 0);
    }

    sdlUpdate();

    for(;;) sdlMilliSleep(80);

    sdlExit;

}
