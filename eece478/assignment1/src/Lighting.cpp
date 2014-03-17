#include "Lighting.h"

#include <cstring>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

using namespace std;

int Lighting::TotalNumLight = 0;

Lighting::Lighting()
{
  //check if total lights count is exceeded
  if(Lighting::TotalNumLight+1 >= GL_MAX_LIGHTS)
  {
    this->bFunctional = false;
  }
  else
  {
    //increment total count of lights
    this->NumLight = Lighting::TotalNumLight + 1;
    Lighting::TotalNumLight++;
    this->bFunctional = true;
  }
}

void Lighting::TurnOn()
{
  if(this->bFunctional == false)
    return;

  glEnable(GL_LIGHT0 + this->NumLight);
}

void Lighting::TurnOff()
{
  if(this->bFunctional == false)
    return;
  
  glDisable(GL_LIGHT0 + this->NumLight);
}

void Lighting::SetLightParam(float amb[], float spec[], float dif[], float pos[])
{
  if(this->bFunctional == false)
    return;

  for(int i = 0; i < 4; i++)
  {
    this->LightAmbiance[i] = amb[i];
    this->LightSpecular[i] = spec[i];
    this->LightDiffuse[i] = dif[i];
    this->LightPosition[i] = pos[i];
  }
}

void Lighting::SetLightParamSpot(float dir[], float exponent, float cutoff)
{
  for(int i = 0; i < 4; i++)
  {
    this->LightDirection[i] = dir[i];
  }
  this->LightExponent = exponent;
  this->LightCutoff = cutoff;
}

void Lighting::SetLightAttenuation(string type, float att)
{
  if(strcmp(type.c_str(),"CONSTANT") == 0)
  {
    this->LightAttenConst = att;
  }
  else if(strcmp(type.c_str(),"LINEAR") == 0)
  {
    this->LightAttenLinear = att;
  }
  else if(strcmp(type.c_str(),"QUADRATIC") == 0)
  {
    this->LightAttenQuadratic = att;
  }
}

void Lighting::SetType(string type)
{
  this->LightType = type;
}

string Lighting::GetType()
{
  return this->LightType;
}

void Lighting::Draw()
{

  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_DIRECTION, this->LightDirection);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_EXPONENT, &this->LightExponent);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_CUTOFF, &this->LightCutoff);

  glLightfv(GL_LIGHT0 + this->NumLight, GL_CONSTANT_ATTENUATION, &this->LightAttenConst);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_LINEAR_ATTENUATION, &this->LightAttenLinear);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_QUADRATIC_ATTENUATION, &this->LightAttenQuadratic);

  glLightfv(GL_LIGHT0 + this->NumLight, GL_AMBIENT, this->LightAmbiance);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPECULAR, this->LightSpecular);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_DIFFUSE, this->LightDiffuse);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_POSITION, this->LightPosition);
}
