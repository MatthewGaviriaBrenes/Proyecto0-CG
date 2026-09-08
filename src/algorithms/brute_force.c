#include <stdlib.h>
#include <math.h>

#include "brute_force.h"
#include "plot.h"

void brute_force(int x0, int y0, int x1, int y1)
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
     * Si X tiene la mayor densidad de puntos,
     * recorremos X y calculamos Y.
     */
    if (adx >= ady)
    {
        double m = (double)dy / (double)dx;
        double b = (double)y0 - m * (double)x0;

        int sx = (dx >= 0) ? 1 : -1;
        int x = x0;

        while (1)
        {
            double y = m * (double)x + b;

            plot(x, (int)round(y));

            if (x == x1)
                break;

            x += sx;
        }
    }
    /*
     * Si Y tiene la mayor densidad de puntos,
     * recorremos Y y calculamos X.
     */
    else
    {
        double m = (double)dx / (double)dy;
        double b = (double)x0 - m * (double)y0;

        int sy = (dy >= 0) ? 1 : -1;
        int y = y0;

        while (1)
        {
            double x = m * (double)y + b;

            plot((int)round(x), y);

            if (y == y1)
                break;

            y += sy;
        }
    }
}
