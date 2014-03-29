#include "Lighting.h"

#include <cstring>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>

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

void Lighting::FormatAction()
{
  int count = 0;
  int size = vAction.size();

  if(size < 1)
    return;

  float data[4];

  string action = vAction[0];

#ifdef DEBUG
  cout<<action<<endl;
  cout<<"actionsize: "<<size<<endl;
#endif

  for(int i = 0; i < size-1; i++)
  {
    data[i] = atof(vAction[i+1].c_str());
  }

  if(action == "light_ambient")
  {
    this->SetLightAmbient(data);
  }
  else if(action == "light_specular")
  {
    this->SetLightSpecular(data);
  }
  else if(action == "light_diffuse")
  {
    this->SetLightDiffuse(data);
  }
  else if(action == "light_position")
  {
    this->SetLightPosition(data);
  }
  else if(action == "light_direction")
  {
    this->SetLightDirection(data);
  }
  else if(action == "light_exponent")
  {
    this->SetLightExponent(data);
  }
  else if(action == "light_cutoff")
  {
    this->SetLightCutoff(data);
  }
  else if(action == "light_atten_linear")
  {
    this->SetLightAttenuation("LINEAR", data[0]);
  }
  else if(action == "light_atten_quadratic")
  {
    this->SetLightAttenuation("QUADRATIC", data[0]);
  }
  else if(action == "light_atten_constant")
  {
    this->SetLightAttenuation("CONSTANT", data[0]);
  }
  else if(action == "light_turnon")
  {
    this->TurnOn();
  }
  else if(action == "light_turnoff")
  {
    this->TurnOff();
  }
}

void Lighting::SetLightAmbient(float in[])
{
  for(int i = 0; i < 4; i++)
  {
    this->LightAmbiance[i] = in[i];
  } 
}

void Lighting::SetLightSpecular(float in[])
{
  for(int i = 0; i < 4; i++)
  {
    this->LightSpecular[i] = in[i];
  }
}

void Lighting::SetLightDiffuse(float in[])
{
  for(int i = 0; i < 4; i++)
  {
    this->LightDiffuse[i] = in[i];
  }
}

void Lighting::SetLightPosition(float in[])
{
  for(int i = 0; i < 4; i++)
  {
    this->LightPosition[i] = in[i];
  }
}

void Lighting::SetLightDirection(float in[])
{
  for(int i = 0; i < 4; i++)
  {
    this->LightDirection[i] = in[i];
  }
}

void Lighting::SetLightExponent(float in[])
{
  this->LightExponent = in[0];
}
void Lighting::SetLightCutoff(float in[])
{
  this->LightCutoff = in[0];
}
