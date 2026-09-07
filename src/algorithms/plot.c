#include <GL/gl.h>
//#include <stdio.h>
#include "plot.h"

void plot_empty(int x, int y)
{
    (void)x;
    (void)y;
}
void plot_glut(int x, int y)
{
    //printf("(%d, %d)\n", x, y);
    //Test momentaneo
    glVertex2i(x, y);
}