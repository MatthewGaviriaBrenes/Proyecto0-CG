#ifndef PLOT_H
#define PLOT_H

typedef void (*PlotFunction)(int x, int y);

void plot_empty(int x, int y);
void plot_glut(int x, int y);

#endif