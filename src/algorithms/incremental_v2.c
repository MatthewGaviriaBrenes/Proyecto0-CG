#include <stdlib.h>
#include <math.h>

#include "incremental_v2.h"
#include "plot.h"

void incremental_v2(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int adx = abs(dx);
    int ady = abs(dy);

    int steps = (adx > ady) ? adx : ady;

    /*
     * Si los dos puntos son iguales,
     * solamente se dibuja ese píxel.
     */
    if (steps == 0)
    {
        plot(x0, y0);
        return;
    }

    /*
     * Calculamos cuánto debe avanzar cada
     * coordenada en cada iteración.
     */
    double paso_x = (double)dx / (double)steps;
    double paso_y = (double)dy / (double)steps;

    double x = (double)x0;
    double y = (double)y0;

    int i;

    for (i = 0; i <= steps; i++)
    {
        plot((int)round(x), (int)round(y));

        x += paso_x;
        y += paso_y;
    }
}
