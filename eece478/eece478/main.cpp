//flag set to bypass initialization problem with GLUT
#define GLUT_DISABLE_ATEXIT_HACK

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>  

#include <iostream>
#include <cmath>

#include "ModelParse.h"
#include "ModelEntity.h"

using namespace std;

namespace glut_global
{
  //parser
  ModelParse cParser;

  vector<ModelEntity*> vpEntity;

  //vertex buffer object ID
  GLuint vVbo;
  
  float * pVerticeData;		// holder of model vertices
  int vNumData;

  //model states

  //modelview states
  float vCamRotX = 0;
  float vCamRotY = 0;
  float vCamRotOldX = 0;
  float vCamRotOldY = 0;

  float vScale = 0;
  float vScaleOld = 0;

  float vModelScaling[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};  

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
  bool bKeyQDown = false;
  bool bKeyCDown = false;
  bool bKeyVDown = false;

  //window dimenstions
  int vWidth;
  int vHeight;
}

using namespace glut_global;

void myIdle()
{
  glutPostRedisplay();
}

void fKeyboardDown(unsigned char key, int x, int y)
/**
   WASD key down detection
*/
{
  if(key == 'w')
    bKeyWDown = true;

  if(key == 'a')
    bKeyADown = true;

  if(key == 's')
    bKeySDown = true;
    
  if(key == 'd')
    bKeyDDown = true;

  if(key == 'q')
    bKeyQDown = !bKeyQDown;  
  
  if(key == 'c')
    bKeyCDown = true;

  if(key == 'v')
    bKeyVDown = true;

  glutPostRedisplay();
}

void fKeyboardUp(unsigned char key, int x, int y)
/**
   WASD key up detection
*/
{
  if(key == 'w')
    bKeyWDown = false;

  if(key == 'a')
    bKeyADown = false;

  if(key == 's')
    bKeySDown = false;
    
  if(key == 'd')
    bKeyDDown = false;
    
  if(key == 'c')
    bKeyCDown = false;

  if(key == 'v')
    bKeyVDown = false;

  glutPostRedisplay();
}

void fMouseDown(int button, int state, int x, int y) 
/**
   mouse down and up detection
 */
{ 
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
#ifdef DEBUG
      cout<<"left mouse: "<< vMouseDx <<", "<< vMouseDy <<endl;
#endif
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
  gluPerspective(120, (float)width / height, 1, 10000);
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
 
	glColor3d(1, 1, 1);

	//reset matrix
	glLoadIdentity();
	
	//save state model stack
	glPushMatrix();
		
	//additional translation from WASD keys
	vTransX = 0;
	vTransY = 0;
	vTransZ = 0;

	vTransZ += (bKeyWDown)? 0.3: 0;
        vTransX += (bKeyADown)? 0.3: 0;
        vTransZ += (bKeySDown)? -0.3: 0;
	vTransX += (bKeyDDown)? -0.3: 0;
        vTransY += (bKeyCDown)? -0.3: 0;
	vTransY += (bKeyVDown)? 0.3: 0;
	
	//save translation
	glPushMatrix();     
	  glLoadIdentity();
	  glTranslatef(vTransX,vTransY,vTransZ);
	  glMultMatrixf(vModelTranslation);
	  glGetFloatv(GL_MODELVIEW_MATRIX,vModelTranslation);
	glPopMatrix();

	//apply additional translation from WASD key movement
	glMultMatrixf(vModelTranslation);

		//lastly translate object
		glTranslatef(0,0,-130);

		//apply rotation transform if only left mouse is down
		if(bMouseLeftDown && !bKeyShiftDown)
		{
		  vCamRotY = vMouseDx/1.f;
		  vCamRotX = vMouseDy/1.f;

		  //save rotation transform to a matrix
		  glPushMatrix();     
		    glLoadIdentity(); // reset
		    //3rd, apply additional rotation transform
		    glRotatef(abs(vCamRotX-vCamRotOldX),vCamRotX-vCamRotOldX,0,0);
		    glRotatef(abs(vCamRotY-vCamRotOldY),0,vCamRotY-vCamRotOldY,0);
		    //2nd,update rotation delta
		    vCamRotOldX = vCamRotX;
		    vCamRotOldY = vCamRotY;
		    //first apply current rotation transform
		    glMultMatrixf(vModelRotation);
		    //lastly, save the new rotation transform
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
			vScale = -vMouseDy/3000.f;

			//save scaling transform to a matrix
			glPushMatrix();     
			  glLoadIdentity(); // reset

			  //apply scaling transform
			  float DeltaScale = 1+vScale-vScaleOld;
			  DeltaScale = DeltaScale<0? 0: DeltaScale;

			  glScalef(DeltaScale,DeltaScale,DeltaScale);

			  vScaleOld = vScale;

			  //first apply current scaling transform
			  glMultMatrixf(vModelScaling);
			  //lastly, save the new scaling transform
			  glGetFloatv(GL_MODELVIEW_MATRIX,vModelScaling);
			glPopMatrix();
		}
		{
		  vScale = 0;
		  vScaleOld = 0;
		}

		//apply saved scaling transform
		glMultMatrixf(vModelScaling);

		if(!bKeyQDown)
		{
		  //place teapot
		  glutWireTeapot(20);
		}
		else
		{
		  //activate VBO and place input model
		  glBindBuffer(GL_ARRAY_BUFFER, vVbo);
		  glVertexPointer(3, GL_FLOAT, 0, 0);
		  glEnableClientState(GL_VERTEX_ARRAY);
		  glDrawArrays(GL_TRIANGLES, 0, vNumData/3/sizeof(GLfloat));
		}

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

	// glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void init (void) 
/**
  setup background colour
  setup projection transformation
  setup vertex buffer and load model vertex
*/
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // setup vertex buffer object
    glGenBuffers(1, &vVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vVbo);

    //load vertices from parsed model data
    vpEntity.at(0)->Update();
    vpEntity.at(0)->GetUpdatedVertices(pVerticeData, vNumData);
    glBufferData(GL_ARRAY_BUFFER, vNumData*sizeof(GLfloat), pVerticeData, GL_STATIC_DRAW);
}

void fExit()
{
  delete pVerticeData;
  cout<<"exited program"<<endl;
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
  
  if(argc == 1)
  { 
    cout<<"not enough argument"<<endl;
    return -1;
  }

  //parse model
  ModelEntity * pcEntity = cParser.GetEntity(argv[1]);
  vpEntity.push_back(pcEntity);

  //boilerplate
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Assignment 1");
  
  //initialize glew for vertex shader
  GLenum err = glewInit();
  if(GLEW_OK != err)
  {
    cout<<"glew init failed"<<endl;
    return -1;
  }

  glEnable(GL_POLYGON_SMOOTH);
  glutReshapeFunc(reshape);
  init ();

  //set callback functions
  glutIdleFunc(myIdle);
  glutDisplayFunc(display);
  glutMouseFunc(fMouseDown);
  glutMotionFunc(fMouseMotion);
  glutKeyboardFunc(fKeyboardDown);
  glutKeyboardUpFunc(fKeyboardUp);

  //exit callback
  atexit(fExit);

  //run
  glutMainLoop();
  return 0;
}
