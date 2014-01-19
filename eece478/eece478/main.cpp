#define GLUT_DISABLE_ATEXIT_HACK

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

#include <GL/gl.h>    // /usr/include/GL/gl.h
#include <GL/glut.h>  // Compiles with "gcc OpenGL.c -o test -lglut" on linux

#include <iostream>

using namespace std;

int vMouseOldX;
int vMouseOldY;
int vMouseDx = 0;
int vMouseDy = 0;
bool bMouseLeftDown = false;
bool bKeyShiftDown = false;

float vCamRotX = 0;
float vCamRotY = 0;
float vCamTraX = 0;

void myIdle()
{
	if(bMouseLeftDown || bKeyShiftDown)
	{
		glutPostRedisplay();
	}
}

void fMouseDown(int button, int state, int x, int y) {
 
	vMouseOldX = x; 
	vMouseOldY = y;
	bMouseLeftDown = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);

	//detect shift key is pressed
	int mod = glutGetModifiers();	
	bKeyShiftDown = (mod == GLUT_ACTIVE_SHIFT);

	if(bMouseLeftDown == false)
	{
		vMouseDx = 0;
		vMouseDy = 0;
	}
}

void fMouseMotion(int x, int y)
{
	if(bMouseLeftDown)
	{
		vMouseDx = x - vMouseOldX;
		vMouseDy = y - vMouseOldY;
		cout<<"left mouse: "<< vMouseDx <<", "<< vMouseDy <<endl;

		glutPostRedisplay();
	}
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)width / height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glMatrixMode(GL_MODELVIEW);
/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glLoadIdentity();

	glTranslatef(0,0,-13);
	
	//camera translation
	if(bMouseLeftDown && !bKeyShiftDown)
	{
		vCamTraX += vMouseDx/200.f;
	}
	glTranslatef(vCamTraX,0,0);

	//camera aim
	if(bMouseLeftDown && bKeyShiftDown)
	{
		vCamRotX += vMouseDx/30.f;
		vCamRotY += vMouseDy/30.f;
	}
	glRotatef(vCamRotX,0,1,0);
	glRotatef(vCamRotY,1,0,0);


	/*gluLookAt(vMouseDx/10.f,vMouseDy/10.f, -3.0f,
	0.f, 0.f, 0.f,
	0.0f, 1.0f,  0.0f);
*/
    glColor3d(1, 0, 0);
    
	glPushMatrix();

    glutWireTeapot(1);

	glPopMatrix();
    
	glutSwapBuffers();
}

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/* 
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (250, 250); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
	glutReshapeFunc(reshape);
    init ();
	glutIdleFunc(myIdle);
    glutDisplayFunc(display);
	glutMouseFunc(fMouseDown);
	glutMotionFunc(fMouseMotion); //mouse motion when mouse/keyboard is pressed
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}