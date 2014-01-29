#define GLUT_DISABLE_ATEXIT_HACK

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

#include <GL/gl.h>
#include <GL/glut.h>  

#include <iostream>
#include <cmath>

using namespace std;

namespace glut_global
{
  
  //model states

  //modelview states
  float vCamRotX = 0;
  float vCamRotY = 0;
  float vCamRotOldX = 0;
  float vCamRotOldY = 0;

  float vScale = 1;
  
  float vModelRotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  float vTransX = 0;
  float vTransY = 0;
  float vTransZ = 0;

  float vModelTranslation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  //mouse and key states
  int vMouseOldX;
  int vMouseOldY;
  int vMouseDx = 0;
  int vMouseDy = 0;
  bool bMouseLeftDown = false;
  bool bKeyShiftDown = false;

  bool bKeyWDown = false;
  bool bKeyADown = false;
  bool bKeySDown = false;
  bool bKeyDDown = false;

  bool bKeyWUp = false;
  bool bKeyAUp = false;
  bool bKeySUp = false;
  bool bKeyDUp = false;

  //window dimenstions
  int vWidth;
  int vHeight;
}

using namespace glut_global;

void myIdle()
{
	// if(bMouseLeftDown || bKeyShiftDown)
	// {
		
	// }
	glutPostRedisplay();
}

void fKeyboardDown(unsigned char key, int x, int y)
{
  if(key == 'w')
    bKeyWDown = true;

  if(key == 'a')
    bKeyADown = true;

  if(key == 's')
    bKeySDown = true;
    
  if(key == 'd')
    bKeyDDown = true;
  
  glutPostRedisplay();
}

void fKeyboardUp(unsigned char key, int x, int y)
{
  if(key == 'w')
    bKeyWDown = false;

  if(key == 'a')
    bKeyADown = false;

  if(key == 's')
    bKeySDown = false;
    
  if(key == 'd')
    bKeyDDown = false;
    
  glutPostRedisplay();
}

void fMouseDown(int button, int state, int x, int y) {
 
	vMouseOldX = x; 
	vMouseOldY = y;
	bMouseLeftDown = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);

	//detect shift key is pressed
	int mod = glutGetModifiers();	
	bKeyShiftDown = (mod == GLUT_ACTIVE_SHIFT);

	if(!bMouseLeftDown)	// reset mouse delta when left mouse is up
	{
	  vMouseDx = 0;
	  vMouseDy = 0;
	}
	glutPostRedisplay();
}

void fMouseMotion(int x, int y)
/** calculate left mouse delta and shift key state
*/
{
	//detect shift key is pressed
	int mod = glutGetModifiers();	
	bKeyShiftDown = (mod == GLUT_ACTIVE_SHIFT);

	if(bMouseLeftDown)
	{
		vMouseDx = x - vMouseOldX;
		vMouseDy = y - vMouseOldY;
		cout<<"left mouse: "<< vMouseDx <<", "<< vMouseDy <<endl;

	}
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	vWidth = width;
	vHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (float)width / height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
/**
basic order of drawing operation:
1.push current model/projection
  a.model
    i.translate transform
    ii.rotate transform
    iii.scale transform
  b.projection
    i.apply projection transform
2.draw object
3.pop restore previous model/projection
*/
{
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glColor3d(1, 0, 0);

	//reset matrix
	glLoadIdentity();
	
	//save state model stack
	glPushMatrix();
		
	//additional translation from keys
	vTransX = 0;
	vTransY = 0;
	vTransZ = 0;

	vTransZ += (bKeyWDown)? 0.04: 0;
        vTransX += (bKeyADown)? 0.04: 0;
        vTransZ += (bKeySDown)? -0.04: 0;
	vTransX += (bKeyDDown)? -0.04: 0;
	
	//save translation
	glPushMatrix();     
	  glLoadIdentity();
	  glTranslatef(vTransX,vTransY,vTransZ);
	  glMultMatrixf(vModelTranslation);
	  glGetFloatv(GL_MODELVIEW_MATRIX,vModelTranslation);
	glPopMatrix();

	glMultMatrixf(vModelTranslation);

		//lastly translate object
		glTranslatef(0,0,-5);

		//apply rotation transform if only left mouse is down
		if(bMouseLeftDown && !bKeyShiftDown)
		{
		  vCamRotY = vMouseDx/1.f;
		  vCamRotX = vMouseDy/1.f;

		  //save rotation transform to a matrix
		  glPushMatrix();     
		    glLoadIdentity(); // reset
		    //then apply additional rotation transform
		    glRotatef(abs(vCamRotX-vCamRotOldX),vCamRotX-vCamRotOldX,0,0);
		    glRotatef(abs(vCamRotY-vCamRotOldY),0,vCamRotY-vCamRotOldY,0);
		    //update rotation delta
		    vCamRotOldX = vCamRotX;
		    vCamRotOldY = vCamRotY;
		    //first apply current rotation transform
		    glMultMatrixf(vModelRotation);
		    //lastly save the new rotation transform
		    glGetFloatv(GL_MODELVIEW_MATRIX,vModelRotation);
		  glPopMatrix();
		}
		else //reset rotation delta when left mouse is up
		{
		  vCamRotY = 0;
		  vCamRotX = 0;
		  vCamRotOldY = 0;
		  vCamRotOldX = 0;
		}

		//apply rotation transform from saved matrix
		glMultMatrixf(vModelRotation);

		//scale object and avoid negative scaling
		if(bMouseLeftDown && bKeyShiftDown)
		{
			vScale -= vMouseDy/1000.f;
			vScale = vScale<0? 0: vScale;
		}
		glScalef(vScale,vScale,vScale);

		//place model
		glutWireTeapot(1);

	//revert state model stack
	glPopMatrix();

	//setup projection for text overlay
	glMatrixMode(GL_PROJECTION);

	//save state projection stack
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, vWidth, 0.0, vHeight); // apply parallel projection transform for text display

		glMatrixMode(GL_MODELVIEW);
		//save state model stack
		glPushMatrix();
			glLoadIdentity();

			// Draw text at bottom right
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glRasterPos2i(vWidth-70, 20);
			string name = "Bill Liu";
			for(int i = 0; i < name.length(); i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, name[i]);
			}
		//revert state model stack
		glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	//revert state projection stack
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
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
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    glEnable(GL_POLYGON_SMOOTH);
    glutReshapeFunc(reshape);
    init ();
    glutIdleFunc(myIdle);
    glutDisplayFunc(display);
    glutMouseFunc(fMouseDown);
    glutMotionFunc(fMouseMotion); //mouse motion when mouse/keyboard is pressed
    glutKeyboardFunc(fKeyboardDown);
    glutKeyboardUpFunc(fKeyboardUp);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
