#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "algorithms/midpoint.h"
#include "algorithms/brute_force.h"
#include "algorithms/incremental.h"
#include "algorithms/incremental_v2.h"

typedef struct
{
    int x0, y0, x1, y1;
} Line;

//global variables glut
Line *lines;
int num_lines, resolution, repetitions;

void draw_scene ();


//Funciones---------------------------------------------
void midpoint_run(PlotFunction plot, int reps)
{
    //Draw lines
    for (int r = 0; r < reps; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            midpoint(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

void midpoint_asm_run(PlotFunction plot, int reps)
{   
    //Draw lines
    for (int r = 0; r < reps; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            midpoint_asm(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

void brute_force_run(PlotFunction plot, int reps)
{
    //Draw lines
    for (int r = 0; r < reps; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            brute_force(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

void incremental_run(PlotFunction plot, int reps)
{
    //Draw lines
    for (int r = 0; r < reps; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            incremental(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

void incremental_v2_run(PlotFunction plot, int reps)
{
    //Draw lines
    for (int r = 0; r < reps; r++)
    {
        for (int i = 0; i < num_lines; i++)
        {
            incremental_v2(lines[i].x0, lines[i].y0,
                lines[i].x1, lines[i].y1,
                plot);
        }
    }
}

int get_repetitions(int divisor)
{
    int reps = repetitions / divisor;

    if (reps < 1)
        reps = 1;

    return reps;
}

double get_time(void)
{
    struct timespec time;

    clock_gettime(CLOCK_MONOTONIC, &time);

    return time.tv_sec + time.tv_nsec / 1000000000.0;
}

double measure_brute_force_empty(void)
{
    double start, end;

    start = get_time();

    brute_force_run(plot_empty, get_repetitions(1));

    end = get_time();

    return end - start;
}

double measure_inc_empty(void)
{
    double start, end;

    start = get_time();

    incremental_run(plot_empty, get_repetitions(10));

    end = get_time();

    return end - start;
}

double measure_inc_v2_empty(void)
{
    double start, end;

    start = get_time();

    incremental_v2_run(plot_empty, get_repetitions(100));

    end = get_time();

    return end - start;
}

double measure_midpoint_empty(void)
{
    double start, end;

    start = get_time();

    midpoint_run(plot_empty, get_repetitions(1000));

    end = get_time();

    return end - start;
}

double measure_midpoint_asm_empty(void)
{
    double start, end;

    start = get_time();

    midpoint_asm_run(plot_empty, get_repetitions(10000));

    end = get_time();

    return end - start;
}

void draw_scene(void)
{
    double start, end,time_mid_empty, time_asm_empty, 
    time_brute_empty, time_inc_empty, time_inc_v2_empty;

    glClear(GL_COLOR_BUFFER_BIT);

    //brute_force.c-Red ==============================
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    start = get_time();

    brute_force_run(plot_glut, get_repetitions(1));

    end = get_time();

    printf("Brute Force - plot GLUT: %.9f seconds\n", (end - start));

    time_brute_empty = measure_brute_force_empty();

    printf("Brute Force - plot empty: %.9f seconds\n", time_brute_empty);

    glEnd();
    glFlush();

    sleep(2);

    //incremental.c- ==============================
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    start = get_time();

    incremental_run(plot_glut, get_repetitions(1));

    end = get_time();

    printf("Incremetal - plot GLUT: %.9f seconds\n", (end - start));

    time_inc_empty = measure_brute_force_empty();

    printf("Incremental - plot empty: %.9f seconds\n", time_inc_empty);

    glEnd();
    glFlush();

    sleep(2);

    //incremental_v2.c- ==============================
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);

    start = get_time();

    incremental_v2_run(plot_glut, get_repetitions(1));

    end = get_time();

    printf("Incremetal_V2 - plot GLUT: %.9f seconds\n", (end - start));

    time_inc_v2_empty = measure_brute_force_empty();

    printf("Incremental_V2 - plot empty: %.9f seconds\n", time_inc_v2_empty);

    glEnd();
    glFlush();

    sleep(2);

    //midpoint.c-Blue ==============================
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);

    start = get_time();

    midpoint_run(plot_glut, get_repetitions(1000));

    end = get_time();

    printf("Midpoint C - plot GLUT: %.9f seconds\n", (end - start));

    time_mid_empty = measure_midpoint_empty();

    printf("Midpoint C - plot empty: %.9f seconds\n", time_mid_empty);

    glEnd();
    glFlush();

    sleep(2);

    //midpoint.asm-Green =========================
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);

    start = get_time();

    midpoint_asm_run(plot_glut, get_repetitions(10000));

    end = get_time();

    printf("Midpoint ASM - plot GLUT: %.9f seconds\n", end - start);

    time_asm_empty = measure_midpoint_asm_empty();

    printf("Midpoint ASM - plot empty: %.9f seconds\n", time_asm_empty);

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
    glutCreateWindow("P0-CG - Algorithms");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-0.5, resolution-0.5, 
        -0.5, resolution-0.5);
    glutDisplayFunc(draw_scene);//draw scene
    glutMainLoop();

    free(lines);

    return 0;
}