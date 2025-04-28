#include <GL/glut.h>
#include <cmath>

float camX = 1.5f, camZ = 1.5f, angle = 0.0f;
float speed = 0.1f;

int maze[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// Function to draw a cube with different blue colors for each face
void drawCube(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.5f, z);

    // Define the colors for each face of the cube (different shades of blue)
    GLfloat colors[6][3] = {
        {0.2f, 0.3f, 0.7f}, // front face
        {0.3f, 0.5f, 1.0f}, // back face
        {0.1f, 0.2f, 0.5f}, // left face
        {0.4f, 0.6f, 1.0f}, // right face
        {0.0f, 0.4f, 0.8f}, // top face
        {0.1f, 0.3f, 0.6f}  // bottom face
    };

    // Draw the front face (z = 1)
    glBegin(GL_QUADS);
    glColor3fv(colors[0]);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    // Draw the back face (z = -1)
    glBegin(GL_QUADS);
    glColor3fv(colors[1]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    // Draw the left face (x = -1)
    glBegin(GL_QUADS);
    glColor3fv(colors[2]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Draw the right face (x = 1)
    glBegin(GL_QUADS);
    glColor3fv(colors[3]);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    // Draw the top face (y = 1)
    glBegin(GL_QUADS);
    glColor3fv(colors[4]);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    // Draw the bottom face (y = -1)
    glBegin(GL_QUADS);
    glColor3fv(colors[5]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

// Function to draw a simple trophy (a golden cone)
void drawTrophy(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.5f, z);

    // Draw the base of the trophy (a small cylinder)
    glColor3f(1.0f, 0.8f, 0.0f); // Gold color
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.2, 0.5, 20, 20); // Trophy base (cone)
    glPopMatrix();

    glPopMatrix();
}

void drawMaze()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (maze[i][j] == 1)
                drawCube(i, j);

    // Draw the trophy at position (1,1)
    drawTrophy(1.0f, 8.0f);
}
void drawPlayer()
{
    // Player position offset in front of the camera
    float offsetX = camX + sin(angle) * 0.5f;
    float offsetZ = camZ - cos(angle) * 0.5f;

    glPushMatrix();
    glTranslatef(offsetX, 0.5f, offsetZ);
    glColor3f(1.0f, 0.0f, 0.0f);    // Red player
    glutSolidSphere(0.03f, 10, 10); // Player is a red sphere
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, 0.5f, camZ,
              camX + sin(angle), 0.5f, camZ - cos(angle),
              0, 1, 0);

    drawMaze();
    drawPlayer(); // <--- Add this line
    glutSwapBuffers();
}

void update()
{
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    float nextX = camX, nextZ = camZ;

    if (key == 'w')
    {
        nextX += sin(angle) * speed;
        nextZ -= cos(angle) * speed;
    }
    if (key == 's')
    {
        nextX -= sin(angle) * speed;
        nextZ += cos(angle) * speed;
    }
    if (key == 'a')
        angle -= 0.1f;
    if (key == 'd')
        angle += 0.1f;

    int mazeX = int(nextX + 0.5f), mazeZ = int(nextZ + 0.5f);
    if (maze[mazeX][mazeZ] == 0)
    {
        camX = nextX;
        camZ = nextZ;
    }
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, 1.0 * 800 / 600, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 3D Maze with Trophy");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}