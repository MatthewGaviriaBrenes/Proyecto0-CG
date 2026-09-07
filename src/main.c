#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "algorithms/midpoint.h"

typedef struct
{
    int x0, y0, x1, y1;
} Line;

//global variables glut
Line *lines;
int num_lines, resolution, repetitions;

void draw_scene ();


//Funciones---------------------------------------------
void midpoint_run(PlotFunction plot)
{
    //Draw lines
    for (int r = 0; r < repetitions; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            midpoint(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

void midpoint_asm_run(PlotFunction plot)
{
    for (int r = 0; r < repetitions; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            midpoint_asm(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

double get_time(void)
{
    struct timespec time;

    clock_gettime(CLOCK_MONOTONIC, &time);

    return time.tv_sec + time.tv_nsec / 1000000000.0;
}

double measure_midpoint_empty(void)
{
    double start;
    double end;

    start = get_time();

    midpoint_run(plot_empty);

    end = get_time();

    return end - start;
}

double measure_midpoint_asm_empty(void)
{
    double start;
    double end;

    start = get_time();

    midpoint_asm_run(plot_empty);

    end = get_time();

    return end - start;
}

void draw_scene(void)
{
    double start, end, time_empty, time_asm_empty;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);

    start = get_time();

    midpoint_run(plot_glut);

    end = get_time();

    glEnd();

    glFlush();

    printf("Midpoint C - plot GLUT: %.9f segundos\n", (end - start));

    time_empty = measure_midpoint_empty();

    printf("Midpoint C - plot vacio: %.9f segundos\n", time_empty);

    start = get_time();

    midpoint_asm_run(plot_glut);

    end = get_time();

    printf("Midpoint ASM - plot GLUT: %.9f segundos\n", end - start);

    time_asm_empty = measure_midpoint_asm_empty();

    printf("Midpoint ASM - plot vacio: %.9f segundos\n", time_asm_empty);

    glEnd();

    glFlush();
}
//main-----------------------------------------------------
int main(int argc, char **argv)
{
    //check input
    if (argc != 4)
    {
        printf("Usage: %s <resolution> <lines> <repetitions>\n", argv[0]);
        return 1;
    }

    //read input

    //read arguments
    resolution = atoi(argv[1]);
    num_lines = atoi(argv[2]);

    //repetitions
    repetitions = atoi(argv[3]);

    //lines memory
    lines = malloc(num_lines * sizeof(Line));

    if (lines == NULL)
    {
        printf("Memory reserve Error.\n");
        return 1;
    }


    //random generator
    srand(time(NULL));

    //generate lines
    for (int i = 0; i < num_lines; i++)
    {
        lines[i].x0 = rand() % resolution;
        lines[i].y0 = rand() % resolution;

        lines[i].x1 = rand() % resolution;
        lines[i].y1 = rand() % resolution;
    }

    //initialize glut 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(resolution, resolution);
    glutCreateWindow("P0-CG - Midpoint");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-0.5, resolution-0.5, 
        -0.5, resolution-0.5);
    glutDisplayFunc(draw_scene);//draw scene
    glutMainLoop();

    free(lines);

    return 0;
}