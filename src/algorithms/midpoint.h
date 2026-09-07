#ifndef MIDPOINT_H
#define MIDPOINT_H
#include "plot.h"

void midpoint(int x0, int y0, int x1, int y1, PlotFunction plot);
void midpoint_asm(int x0, int y0, int x1, int y1, PlotFunction plot);

#endif