// Drawing a color cube in OpenGL 1.0 style

#include "GL/glut.h"

GLfloat colors[][4] = {
    { 1.0, 0.0, 1.0, 1.0 },  // magenta
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0},
    {1.0,0.0,1.0,1.0}

};

GLfloat verts[][4] = {
    { -0.25, 0.25, 0.0, 1.0 },
    { -0.5,0.0, 0.0, 1.0 },
    { -0.25,- 0.25, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.0, -0.5, 0.0, 1.0 },
    { 0.25, -0.25, 0.0, 1.0 },
    { 0.5, 0.0, 0.0, 1.0 },
    { 0.25, 0.25, 0.0, 1.0 }
};

int nverts = sizeof(verts) / sizeof(verts[0]);

GLint quads[][4] = {
    { 0, 1, 2, 3 },
    { 3, 2, 4, 5 },
    { 3, 5, 6, 7 }
};

int nquads = sizeof(quads) / sizeof(quads[0]);

void colorcube()
{
    glBegin(GL_QUADS);

    for (int i = 0; i < nquads; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            glColor4fv(colors[quads[i][j]]);
            glVertex4fv(verts[quads[i][j]]);
        }
    }

    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    colorcube();

    glutSwapBuffers();
}


// OpenGL initialization
void init(void)
{
    glEnable(GL_DEPTH_TEST);           // Enable desth testing
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Clear the screen to black
}



void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:  // Escape key
    case 'q': case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Color Cube");
    
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

