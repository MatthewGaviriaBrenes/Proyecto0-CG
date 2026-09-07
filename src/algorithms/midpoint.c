#include <stdlib.h>
#include "midpoint.h"

//draw a line between two points with midpoint algorithm
void midpoint(int x0, int y0, int x1, int y1, 
    PlotFunction plot)
{
    int dx, dy, sx, sy, error;
    //abs distances
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    //Determine direction for both x and y
    //1: move right
    //-1: move left
    sx = (x0 < x1) ? 1 : -1; 
    sy = (y0 < y1) ? 1 : -1;

    //variable used to choose next pixel
    error = dx - dy;

    //continue until reaching endpoint
    while (1)
    {
        plot(x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        int error2 = 2 * error;

        if (error2 > -dy)
        {
            error -= dy;
            x0 += sx;
        }

        if (error2 < dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}