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
  this->CurveIndex = 0;
}

CurvePath::~CurvePath()
{
  this->vpParametricCurve.clear();
}

void CurvePath::AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[])
{
  ParametricCurve * pcurve = new ParametricCurve();
  
  pcurve->SetParameter(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);

  this->vpParametricCurve.push_back(pcurve);
}
  
void CurvePath::Increment()
{
  if(this->vpParametricCurve.empty())
    return;

  this->itCurve = this->vpParametricCurve.begin();
  this->itCurve += this->CurveIndex;

  if(this->itCurve != this->vpParametricCurve.end())
  {  
    // initialize curve 
    if((*itCurve)->Started() == false)
    {
      (*itCurve)->Start(); 
    }
    
    if((*itCurve)->Done() == false)
    {
      // update current curve
      float * pPosition = &this->Position[0];   
      (*itCurve)->GetCurrent(pPosition);
      (*itCurve)->Increment();
    }
    else
    {
      //go to next curve if current curve is finished
      this->CurveIndex++;
    }
  }
  this->ApplyTranslate(this->Position);
}

void CurvePath::Draw()
{
  glBegin(GL_POINTS);
    glColor3f(1,1,1);
    // position is actually transformed using ModelTransform's ApplyTranslate in Increment function
    glVertex3f(0,0,0);
  glEnd();
}

void CurvePath::PrintPosition()
{

  for(int i = 0; i < 3; i++)
  {
    cout<<this->Position[i]<<" ";
  }
  cout<<endl;
}
