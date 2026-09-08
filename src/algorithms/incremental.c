#include <stdlib.h>
#include <math.h>

#include "incremental.h"
#include "plot.h"

void incremental(int x0, int y0, int x1, int y1, 
    PlotFunction plot)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int adx = abs(dx);
    int ady = abs(dy);

    /*
     * Si la línea es vertical, recorremos Y.
     */
    if (dx == 0)
    {
        int sy = (dy >= 0) ? 1 : -1;
        int y = y0;

        while (1)
        {
            plot(x0, y);

            if (y == y1)
                break;

            y += sy;
        }

        return;
    }

    /*
     * X es el eje con mayor densidad.
     */
    if (adx >= ady)
    {
        double m = (double)dy / (double)dx;
        double y = (double)y0;

        int sx = (dx >= 0) ? 1 : -1;
        int x = x0;

        while (1)
        {
            plot(x, (int)round(y));

            if (x == x1)
                break;

            x += sx;
            y += m * sx;
        }
    }

    /*
     * Y es el eje con mayor densidad.
     */
    else
    {
        double m = (double)dx / (double)dy;
        double x = (double)x0;

        int sy = (dy >= 0) ? 1 : -1;
        int y = y0;

        while (1)
        {
            plot((int)round(x), y);

            if (y == y1)
                break;

            y += sy;
            x += m * sy;
        }
    }
}
