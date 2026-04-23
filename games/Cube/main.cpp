#include <windows.h>

//#include <Gl/gl.h>
//#include <Gl/glu.h>
#include <Gl/glut.h>
#include <math.h>

#include <iostream.h>

#include "cubemanage.h"
#include "wcgcube.h"

static GLfloat PI=3.1415f;
// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat rotate=0.0f;
static int rotateType=0;
static int rotateOK=0;
static int rotateRate=100;
static GLfloat rotateStep=5*PI/180;

CubeManage cm;

// Called to draw scene
void RenderScene(void) {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
  glPushMatrix();

  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	cm.draw(rotateType,rotate);

  glPopMatrix();

	// Show the graphics
	glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);	
//	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
    }

void TimerFunc(int value) {
	if (rotate>=PI/2) {
		cm.turn(rotateType);
		rotateType=0;
		rotateOK=0;
		rotate=0.0f;
		// Refresh the Window
		glutPostRedisplay();
		return;
	}
	rotate+=rotateStep;
	
	// Refresh the Window
	glutPostRedisplay();
	
	glutTimerFunc(rotateRate,TimerFunc,1);
}

void SpecialKeys(int key, int x, int y)
	{
	if (key == GLUT_KEY_F1) {
		if (rotateOK==1)
			return;
		rotateType=1;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F2) {
		if (rotateOK==1)
			return;
		rotateType=2;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F3) {
		if (rotateOK==1)
			return;
		rotateType=3;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F4) {
		if (rotateOK==1)
			return;
		rotateType=4;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F5) {
		if (rotateOK==1)
			return;
		rotateType=5;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F6) {
		if (rotateOK==1)
			return;
		rotateType=6;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F7) {
		if (rotateOK==1)
			return;
		rotateType=7;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F8) {
		if (rotateOK==1)
			return;
		rotateType=8;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F9) {
		if (rotateOK==1)
			return;
		rotateType=9;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F10) {
		if (rotateOK==1)
			return;
		rotateType=10;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F11) {
		if (rotateOK==1)
			return;
		rotateType=11;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if (key == GLUT_KEY_F12) {
		if (rotateOK==1)
			return;
		rotateType=12;
		rotateOK=1;
		rotate=0.0f;
		glutTimerFunc(rotateRate,TimerFunc,1);
	}
	
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
	}


void ChangeSize(int w, int h)
	{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

int main(int argc, char* argv[])
	{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
