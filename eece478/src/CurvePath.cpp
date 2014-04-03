#include "ParametricCurve.h"
#include "CurvePath.h"

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>  

using namespace std;

CurvePath::CurvePath()
{
}

CurvePath::~CurvePath()
{
}

void CurvePath::Draw()
{
  //incrementing logic
  if(this->GetKeepIncrementing() == true)
  {
    this->Increment();
    //save new position
    float pos[3];
    this->GetPosition(pos);
    this->ApplyTranslate(pos);
  }

  glBegin(GL_POINTS);
    glColor3f(1,1,1);
    // position is actually transformed using ModelTransform's ApplyTranslate in Increment function
    glVertex3f(0,0,0);
  glEnd();
}

void CurvePath::FormatAction()
{
  int count = 0;
  for(auto i: vAction)
  {
    if(count == 0)
    {
      if(i == "curve_increment")
      {
	this->SetKeepIncrementing(true);
      }
      else if(i == "curve_stopincrement")
      {
	this->SetKeepIncrementing(false);
      }
    }
  }
}

void CurvePath::AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[])
{
  Interpolate::AddCurve(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);
}
  
