
#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

int ch = 0;
int dx, dy;

// Function to display a point
void display(int x, int y)
{
    glColor3f(0, 0, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to draw a simple line using DDA algorithm
void SimpleLine(int x1, int y1, int x2, int y2)
{
    dx = x2 - x1;
    dy = y2 - y1;
    int steps;
    if (abs(dx) >= abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float Xin = dx / (float)steps;
    float Yin = dy / (float)steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++)
    {
        display(x, y);
        x = x + Xin;
        y = y + Yin;
    }
    glFlush();
}

// Mouse function to handle left and right button clicks
void mouse(int button, int state, int x, int y)
{
    static int x1, y1, pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (pt == 0)
        {
            x1 = x;
            y1 = y;
            pt = pt + 1;
        }
        else
        {
            if (ch == 1)
            {
                SimpleLine(x1, y1, x, y);
            }

            x1 = x;
            y1 = y;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        pt = 0;
    }
    glFlush();
}

// Keyboard function to handle key presses
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
    {
        ch = 1;
        cout << "Simple Line is opted" << endl;
        glutMouseFunc(mouse);
        break;
    }
    }
    glutPostRedisplay();
}

// Function to initialize OpenGL
void initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 600, 600, 0);
}

// Function to draw initial axes
void initialaxis()
{
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(300, 0);
    glVertex2i(300, 600);
    glVertex2i(0, 300);
    glVertex2i(600, 300);
    glEnd();
    glFlush();
    glutKeyboardFunc(keyboard);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("DDA Algorithm");
    initialize();
    cout << "Choose your Line type: " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "s => simple" << endl;
    glutDisplayFunc(initialaxis);
    glutMainLoop();
    return 0;
}
