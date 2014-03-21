#include "ParametricCurve.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>  

using namespace std;

ParametricCurve::ParametricCurve()
{
}

void ParametricCurve::SetParameter(int steps, float control1[], float control2[], float control3[], float control4[])
{

  this->mTotalStep = steps;
  for(int j = 0; j < 3; j++)
  {
    this->mControlPoints[0][j] = control1[j];
    this->mControlPoints[1][j] = control2[j];
    this->mControlPoints[2][j] = control3[j];
    this->mControlPoints[3][j] = control4[j];
  }
}

void ParametricCurve::Increment()
{
  for(int i = 0; i < 3; i++)
  {
    this->mPoint[i] += this->mDPoint[i];
    this->mDPoint[i] += this->mDDPoint[i];
    this->mDDPoint[i] += this->mDDDPoint[i];
    this->mCurrentStep++;
  }
}

void ParametricCurve::GetCurrent(float*& out)
{
  for(int i = 0; i < 3; i++)
  {
    out[i] = this->mPoint[i];
  }
}

void ParametricCurve::Start()
{
  this->mCurrentStep = 0;
  
  float d = 1.f/(this->mTotalStep-1);
  float d2 = d*d;
  float d3 = d*d2;

  float px[4];
  float py[4];
  float pz[4];

  for(int i = 0; i < 4; i++)
  {
    px[i] = this->mControlPoints[i][0];
    py[i] = this->mControlPoints[i][1];
    pz[i] = this->mControlPoints[i][2];
  }

  cout<<"control4:"<<px[3]<<","<<py[3]<<","<<pz[3]<<endl;
  
  float cVec[3][4];
  
  float * pVec = &cVec[0][0];
  float * pLeftSide = px;  
  float * basis = &this->mBezierBasis[0][0];
  this->MatMult(pLeftSide, basis, pVec);
  pLeftSide = py;
  pVec += 4;
  this->MatMult(pLeftSide, basis, pVec);
  pLeftSide = pz;
  pVec += 4;
  this->MatMult(pLeftSide, basis, pVec);

  for(int i = 0; i < 3; i++)
  {
    this->mPoint[i] = mControlPoints[0][i];
  }

  for(int i = 2; i >= 0; i--)
  {
    float a = cVec[i][0];
    float b = cVec[i][1];
    float c = cVec[i][2];

    mDPoint[i] = a * d3 + b * d2 + c * d;
    mDDPoint[i] = 6 * a * d3 + 2 * b * d2;
    mDDDPoint[i] = 6 * a * d3;
  } 
}

bool ParametricCurve::Done()
{
  return (this->mCurrentStep == this->mTotalStep -1);
}

void ParametricCurve::MatMult(float * FourByOne, float * FourbyFour, float *& out)
{
  // for each column
  for(int i = 0; i < 4; i++)
  {
    float sum = 0;
    // for each row
    for(int j = 0; j < 4; j++)
     {
      sum += (FourByOne[j] * FourbyFour[i + j*4]);
      // sum += (FourByOne[j] * FourbyFour[i*4 + j]);
    }    
    out[i] = sum;
  }
}

void ParametricCurve::DrawDebug()
{
  glBegin(GL_POINTS);

    glColor3f(1,1,1);
    glVertex3f(this->mPoint[0], this->mPoint[1], this->mPoint[2]);
  glEnd();

  cout<<this->mPoint[0]<<","<<this->mPoint[1]<<","<<this->mPoint[2]<<endl;
}
