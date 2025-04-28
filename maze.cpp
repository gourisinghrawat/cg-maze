#include <GL/glut.h>
#include <cmath>
#include <cstdio>

float camX = 1.5f, camZ = 1.5f, angle = 0.0f;
float speed = 0.1f;

int points = 0;

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

int food[10][10];

void initFood()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (maze[i][j] == 0)
                food[i][j] = 1;
}

void drawCube(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.5f, z);

    GLfloat colors[6][3] = {
        {0.2f, 0.3f, 0.7f},
        {0.3f, 0.5f, 1.0f},
        {0.1f, 0.2f, 0.5f},
        {0.4f, 0.6f, 1.0f},
        {0.0f, 0.4f, 0.8f},
        {0.1f, 0.3f, 0.6f}};

    glBegin(GL_QUADS);
    glColor3fv(colors[0]);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3fv(colors[1]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3fv(colors[2]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3fv(colors[3]);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3fv(colors[4]);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3fv(colors[5]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

void drawTrophy(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.5f, z);
    glColor3f(1.0f, 0.8f, 0.0f);
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.2, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();
}

void drawFood(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, 0.1f, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.1f, 10, 10);
    glPopMatrix();
}

void drawMaze()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (maze[i][j] == 1)
                drawCube(i, j);
            else if (food[i][j] == 1)
                drawFood(i, j);
        }
    }
    drawTrophy(1.0f, 8.0f);
}

// Removed drawPlayer() completely

void renderBitmapString(float x, float y, void *font, const char *string)
{
    glRasterPos2f(x, y);
    for (const char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, 0.5f, camZ,
              camX + sin(angle), 0.5f, camZ - cos(angle),
              0, 1, 0);

    drawMaze();
    // No drawPlayer()

    // Points display
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    char buffer[50];
    sprintf_s(buffer, "Points: %d", points);

    glColor3f(1, 1, 1);
    renderBitmapString(650, 570, GLUT_BITMAP_HELVETICA_18, buffer);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

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

    float COLLISION_RADIUS = 0.6f;

    bool blocked = false;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dz = -1; dz <= 1; ++dz)
        {
            int checkX = int(nextX + dx);
            int checkZ = int(nextZ + dz);

            if (checkX >= 0 && checkX < 10 && checkZ >= 0 && checkZ < 10)
            {
                if (maze[checkX][checkZ] == 1)
                {
                    float distX = fabs(nextX - checkX);
                    float distZ = fabs(nextZ - checkZ);
                    if (distX < COLLISION_RADIUS && distZ < COLLISION_RADIUS)
                    {
                        blocked = true;
                    }
                }
            }
        }
    }

    if (!blocked)
    {
        camX = nextX;
        camZ = nextZ;

        int mazeX = int(camX + 0.5f);
        int mazeZ = int(camZ + 0.5f);

        if (mazeX >= 0 && mazeX < 10 && mazeZ >= 0 && mazeZ < 10)
        {
            if (food[mazeX][mazeZ] == 1)
            {
                food[mazeX][mazeZ] = 0;
                points++;
            }
        }
    }
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, 1.0 * 800 / 600, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    initFood();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL 3D Maze Game");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
