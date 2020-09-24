#include <GL/freeglut.h>
#include <GL/gl.h>

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "sensor.h"

GLfloat xRotated, yRotated, zRotated;

int width, height;

struct timespec start, end;

#define WIDTH  50
#define HEIGHT 50

float map[WIDTH][HEIGHT];

float nextrand() {
    static float lastRand = 0.5;
    float newRand = (rand() % 1000) / 1000.0;


    newRand = lastRand*0.6+newRand*0.4;
    lastRand = newRand;

    return newRand;
}

void init_map()
{
    int x, y;
    for (x = 0; x < WIDTH; ++ x) {
        for (y = 0; y < HEIGHT; ++ y) {
            map[x][y] = nextrand() * 2;
        }
    }
}

void init(void)
{
    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE); 
    glEnable(GL_DEPTH_TEST);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    init_map();
}

void DrawCube(float x, float y, float z, float xr, float yr, float zr, float s)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(xr,1.0,0.0,0.0);
    glRotatef(yr,0.0,1.0,0.0);
    glRotatef(zr,0.0,0.0,1.0);
    glScalef(s, s, s);

  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
    glPopMatrix();
}

void color(int x, int y) {
    float h = (2 - map[x][y]) * 0.2;
    glColor3f(0.5f - h,1.0f - h,0.4f - h);    // Color Yellow
}

void draw_map(float mx, float my, float mz, float xr, float yr, float zr) {
    int x, y;

    glPushMatrix();
    glTranslatef(mx, my, mz);
    glRotatef(xr,1.0,0.0,0.0);
    glRotatef(yr,0.0,1.0,0.0);
    glRotatef(zr,0.0,0.0,1.0);
    glColor3f(0.5f,1.0f,0.4f);    // Color Yellow
    glBegin(GL_TRIANGLES);
        for (x = 0; x < WIDTH; ++ x) {
            for (y = 0; y < HEIGHT; ++ y) {

                color(x,y+1);
                glVertex3f(x + 0.0f, map[x][y+1], y + 1.0f);
                color(x+1,y);
                glVertex3f(x + 1.0f, map[x+1][y], y + 0.0f);
                color(x,y);
                glVertex3f(x + 0.0f, map[x][y], y + 0.0f);

                color(x+1,y);
                glVertex3f(x + 1.0f, map[x+1][y], y + 0.0f);
                color(x,y+1);
                glVertex3f(x + 0.0f, map[x][y+1], y + 1.0f);
                color(x+1,y+1);
                glVertex3f(x + 1.0f, map[x+1][y+1], y + 1.0f);
            }
        }
    glEnd();
    glPopMatrix();
}

void drawscene(void) {
    draw_map(20, -10, 20, 0, 0, 0);
    DrawCube(20, -9, 20, 90, 0, 0, 1);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
 
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    int space = 20;

//    glRotatef(pitchCam, 1, 0, 0);
    glRotatef(sin(diff * 0.0000005) * 35 - 45 - 180 - 45 / 2, 0, 1, 0); // yaw
//    glRotatef(rollCam, 0, 0, 1);

    glViewport(-space - width/2,0,width,height);  //Use the whole window for rendering
    drawscene();
    glViewport(width/2+space,0,width,height);  //Use the whole window for rendering
    glRotatef(30, 0, 1, 0); // yaw
    drawscene();

    glFlush();
}


void reshape(int w, int h)
{
    if (h == 0 || w == 0) return;  //Nothing is visible then, so return

    width = w;
    height = h;

    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(45.0,(GLdouble)w/(GLdouble)h,1.0, 425.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,w,h);  //Use the whole window for rendering
}

void mouseClicks(int x, int y, int w, int z) {
	exit(0);
}

int main(int argc, char** argv){

    Sensor* sensor = openSensor("/sys/bus/iio/devices/iio\\:device2/in_accel_y_raw");
    int data;

    while(1) {
        if (!readSensor(sensor, &data)) {
            printf("Failed reading data!\n");
            break;
        }

        printf("Data: %d\n", data);
    }

/*
    glutInit(&argc, argv);
    //we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1440/2,720);
    glutCreateWindow(argv[0]);
	glutFullScreen();
    init();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
glutMouseFunc(mouseClicks);
    //Set the function for the animation.
    glutIdleFunc(draw);
    glutMainLoop();
*/
    return 0;
}
 
