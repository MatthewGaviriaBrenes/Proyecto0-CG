#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "algorithms/midpoint.h"

void draw_scene ();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("P0-CG - Midpoint");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-0.5, 400.5, -0.5, 400.5);
    glutDisplayFunc(draw_scene);
    glutMainLoop();

    return 0;
}

void draw_scene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);

    midpoint(2, 2, 8, 5);

    glEnd();

    glFlush();
}