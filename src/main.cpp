#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <corecrt_math_defines.h>

// Window size
const int WIDTH = 1200;
const int HEIGHT = 700;

// Black hole properties
const float BH_RADIUS = 1.0f;
const float ACC_DISK_INNER = 1.5f;
const float ACC_DISK_OUTER = 4.0f;

// Gravity constants
const float G = 4.0f;
const float DT = 0.015f;
const float DAMPING = 0.9995f;


// Grid properties
const int GRID_SIZE = 20;
const float GRID_STEP = 1.0f;

// Rotation
float diskAngle = 0.0f;
float cameraAngle = 20.0f;

// Star particles
struct Star {
    glm::vec3 pos;
    glm::vec3 vel;
};

std::vector<Star> stars;

// Initialize
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2.0f);
    srand((unsigned)time(0));

    for (int i = 0; i < 800; i++) {
        float x = ((rand()%2000)-1000)/50.0f;
        float y = ((rand()%2000)-1000)/50.0f;
        float z = ((rand()%2000)-1000)/50.0f;

        glm::vec3 pos(x,y,z);
        glm::vec3 tangent(-z, 0, x);
        tangent = glm::normalize(tangent) * 0.5f;

        Star s;

        float r = 18.0f;
        float angle = ((float)rand()/RAND_MAX) * 2*M_PI;

        s.pos = glm::vec3(
            cos(angle) * r,
            ((rand() % 100) - 50) / 30.0f,
            sin(angle) * r
        );

        // Tangential velocity for orbit
        glm::vec3 t(-s.pos.z, 0, s.pos.x);
        s.vel = glm::normalize(t) * 0.25f;

        stars.push_back(s);
    }
}

// Gravity update
void updatePhysics() {
    for (auto &s : stars) {

        glm::vec3 dir = -s.pos;
        float dist = glm::length(dir) + 0.05f;

        if (dist < BH_RADIUS) {
            float R = 18.0f;
            float angle = ((float)rand()/RAND_MAX) * 2*M_PI;

            s.pos = glm::vec3(cos(angle)*R,
                              ((rand()%100)-50)/30.0f,
                              sin(angle)*R);

            glm::vec3 t2(-s.pos.z, 0, s.pos.x);
            s.vel = glm::normalize(t2) * 0.35f;

            continue;
        }

        glm::vec3 acc = (G / (dist * dist)) * glm::normalize(dir);

        if (glm::length(acc) > 12.0f)
            acc = glm::normalize(acc) * 12.0f;

        s.vel += acc * DT;
        s.vel *= DAMPING;
        s.pos += s.vel * DT;
    }
}


// Draw warped grid
void drawGrid() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
    for (float i = -GRID_SIZE; i <= GRID_SIZE; i += GRID_STEP) {
        for (float j = -GRID_SIZE; j <= GRID_SIZE; j += GRID_STEP) {
            float z1 = -5.0f / sqrt(i*i + j*j + 1.0f);
            float z2 = -5.0f / sqrt((i+GRID_STEP)*(i+GRID_STEP) + j*j + 1.0f);
            glVertex3f(i, z1, j);
            glVertex3f(i+GRID_STEP, z2, j);

            z2 = -5.0f / sqrt(i*i + (j+GRID_STEP)*(j+GRID_STEP) + 1.0f);
            glVertex3f(i, z1, j);
            glVertex3f(i, z2, j+GRID_STEP);
        }
    }
    glEnd();
}

// Draw BH
void drawBlackHole() {
    glColor3f(0,0,0);
    glutSolidSphere(BH_RADIUS, 50, 50);
}

// Draw disk
void drawAccretionDisk() {
    glPushMatrix();
    glRotatef(diskAngle, 0,1,0);

    glBegin(GL_QUAD_STRIP);
    for (float r = ACC_DISK_INNER; r <= ACC_DISK_OUTER; r += 0.05f) {
        float glow = (ACC_DISK_OUTER - r) / (ACC_DISK_OUTER - ACC_DISK_INNER);
        glColor3f(1.0f, 0.7f*glow, 0.1f);

        for (float a=0; a<=2*M_PI; a+=0.05f) {
            float x = cos(a)*r;
            float z = sin(a)*r;
            glVertex3f(x, 0.05f, z);
            glVertex3f(x, -0.05f, z);
        }
    }
    glEnd();
    glPopMatrix();
}

// Draw stars
void drawStars() {
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    for (auto &s : stars)
        glVertex3f(s.pos.x, s.pos.y, s.pos.z);
    glEnd();
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(12*sin(glm::radians(cameraAngle)), 6, 12*cos(glm::radians(cameraAngle)),
              0,0,0, 0,1,0);

    updatePhysics();

    drawGrid();
    drawAccretionDisk();
    drawBlackHole();
    drawStars();

    diskAngle += 0.5f;
    cameraAngle += 0.15f;

    updatePhysics();

    glutSwapBuffers();
}

// Reshape
void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w/h, 0.1, 200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Realistic 3D Black Hole Simulation");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
