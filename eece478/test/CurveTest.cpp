/// @author Bill Liu #63461081 EECE478 2014 Spring

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
#include <time.h>

#include "ParametricCurve.h"
#include "ModelAbstraction.h"
#include "ModelParse.h"

using namespace std;

///global variables for mouse and key states, transformations, model entity
namespace glut_global
{
  ///parser
  ModelParse cParser;

  ///holder of different input models
  vector<ModelAbstraction*> vpEntity;

  //camera entity
  ModelAbstraction* pCameraEntity;

  ///transformation variables
  float vCamRotX = 0;
  float vCamRotY = 0;
  float vCamRotOldX = 0;
  float vCamRotOldY = 0;

  float vScale = 0;
  float vScaleOld = 0;

  float vTransX = 0;
  float vTransY = 0;
  float vTransZ = 0;

  ///saves transformations of the model
  float vModelTranslation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float vModelScaling[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};  
  float vModelRotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  ///mouse and key states
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

  ///window dimensions
  int vWidth;
  int vHeight;

  ParametricCurve * pCurve;

  clock_t t;
  int time_prev;

  float fps = 0.75; 
}

using namespace glut_global;

void myIdle()
{
  int time;
  
  float duration;

  do
  {
    time = clock();
    duration = (float)(time - time_prev)/CLOCKS_PER_SEC;
  }while(duration < fps);

  if(pCurve->Done() != true)
  {
    pCurve->Increment();
  }

  time_prev = time;

  glutPostRedisplay();
}

void fKeyboardDown(unsigned char key, int x, int y)
/**
   QWASDCV key down detection
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
    bKeyQDown = !bKeyQDown;  	// toggle only for switching models
  
  if(key == 'c')
    bKeyCDown = true;

  if(key == 'v')
    bKeyVDown = true;

  glutPostRedisplay();
}

void fKeyboardUp(unsigned char key, int x, int y)
/**
WASDCV key up detection
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
/** 
calculate left mouse delta and shift key state
*/
{
  //detect shift key is pressed
  int mod = glutGetModifiers();	
  //bKeyShiftDown = (mod == GLUT_ACTIVE_SHIFT);

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
/**
resize window and set perspective parameters
*/
{
  vWidth = width;
  vHeight = height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100, (float)width / height, 1, 10000);
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

  glPushMatrix();

    //reset matrix
    glLoadIdentity();
		
    //additional translation from WASDCV (forward,left,back,right,up,down) keys
    vTransX = 0;
    vTransY = 0;
    vTransZ = 0;

    //delta when key is down
    vTransZ += (bKeyWDown)? 0.3: 0;
    vTransX += (bKeyADown)? 0.3: 0;
    vTransZ += (bKeySDown)? -0.3: 0;
    vTransX += (bKeyDDown)? -0.3: 0;
    vTransY += (bKeyCDown)? -0.3: 0;
    vTransY += (bKeyVDown)? 0.3: 0;

    //apply translation
    
    float DeltaTranslate[3]={0,0,0};
    DeltaTranslate[0] = vTransX;
    DeltaTranslate[1] = vTransY;
    DeltaTranslate[2] = vTransZ;       

    //apply rotation transform if only left mouse is down
    float DeltaRotate[3]={0,0,0};

    if(bMouseLeftDown && !bKeyShiftDown)
    {
      //get rotation delta
      vCamRotY = vMouseDx/1.f;
      vCamRotX = vMouseDy/1.f;

      DeltaRotate[0] = vCamRotX - vCamRotOldX;
      DeltaRotate[1] = vCamRotY - vCamRotOldY;
      DeltaRotate[2] = 0;

      //update rotation delta
      vCamRotOldX = vCamRotX;
      vCamRotOldY = vCamRotY;  
    }
    else //reset rotation delta when left mouse is up
    {
      vCamRotY = 0;
      vCamRotX = 0;
      vCamRotOldY = 0;
      vCamRotOldX = 0;
    }

    //scale object and avoid negative scaling
    float DeltaScale[3] = {0,0,0};
    if(bMouseLeftDown && bKeyShiftDown)
    {
      //get delta
      vScale = -vMouseDy/3000.f;

      for(int j = 0; j < 3; j++)
      {
	DeltaScale[j] = vScale-vScaleOld;
      }

      vScaleOld = vScale;
    }
    else
    {
      vScale = 0;
      vScaleOld = 0;
    }

    //apply transforms to camera
    pCameraEntity->ApplyDeltaTranslate(DeltaTranslate);
    pCameraEntity->ApplyDeltaRotate(DeltaRotate);
    pCameraEntity->ApplyDeltaScale(DeltaScale);

    pCameraEntity->DrawModel();
    
    pCurve->DrawDebug();

  //revert state model stack
  glPopMatrix();
      
  //setup projection for text overlay
  glMatrixMode(GL_PROJECTION);
      
  //save state projection stack
  glPushMatrix();
    glLoadIdentity();
    // apply parallel projection transform for text display
    gluOrtho2D(0.0, vWidth, 0.0, vHeight); 
    
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
    
  glutSwapBuffers();
}

void init (void) 
/**
  setup background colour
  setup projection transformation
  setup vertex buffer and load model vertex
*/
{
    glClearColor (0.3, 0.3, 0.3, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void fExit()
{
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
  
  // if(argc == 1)
  // { 
  //   cout<<"not enough argument"<<endl;
  //   return -1;
  // }

  //boilerplate
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
  glEnable(GL_TEXTURE_2D);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);    
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LIGHTING);
  glutReshapeFunc(reshape);
  init();

  //set callback functions
  glutIdleFunc(myIdle);
  glutDisplayFunc(display);
  glutMouseFunc(fMouseDown);
  glutMotionFunc(fMouseMotion);
  glutKeyboardFunc(fKeyboardDown);
  glutKeyboardUpFunc(fKeyboardUp);

  //exit callback
  atexit(fExit);

  //initialize camera
  pCameraEntity = new ModelAbstraction();

  float trans[] = {0,0,-40};
  pCameraEntity->ApplyDeltaTranslate(trans);

  pCurve = new ParametricCurve();
  float control1[3] = {0,0,0};
  float control2[3] = {0,10,0};
  float control3[3] = {10,10,0};
  float control4[3] = {10,0,0};
  pCurve->SetParameter(40, control1, control2, control3, control4);
  pCurve->Start();

  time_prev = clock();

  //run gl loop
  glutMainLoop();
  return 0;
}
