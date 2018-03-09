
#include <string.h>
#include <iostream>
#include "scene.h"

// windowsize
GLint windowWidth = 512;
GLint windowHeight = 512;
float speed = 500;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glutReshapeWindow(windowWidth, windowHeight);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 033: // Escape Key
    case 'q':
    case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}

void specialkey(int key, int x, int y)
{
    switch (key)
    {
    }
}

void autoRotation(int value)
{
    glutTimerFunc(speed, autoRotation, 0);
}

int main(int argc, char **argv)
{
    /*OpenGL*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("scene");
    glewExperimental = GL_TRUE;
    glewInit();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkey);
    glutTimerFunc(speed, autoRotation, 0);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
