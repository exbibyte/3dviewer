#include "Lighting.h"
#include "Interpolate.h"

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
  float LightAmbianceInterpolate[4];
  float LightSpecularInterpolate[4];
  float LightDiffuseInterpolate[4];

  for(int i = 0; i < 4; i++)
  {
    LightAmbianceInterpolate[i] = this->LightAmbiance[i];
    LightSpecularInterpolate[i] = this->LightSpecular[i];
    LightDiffuseInterpolate[i] = this->LightDiffuse[i];
  }

  //get interpolated values if set
  if(Interpolate::GetActivated() == true)
  {
    //increment interpolation
    if(this->GetKeepIncrementing() == true)
    {
      this->Increment();
      
      float pos[3];
      this->GetPosition(pos);
      // calculate intensities based on interpolated values
      for(int i = 0; i < 3; i++)
      {
	cout<<"light interpolate: "<<pos[0]<<endl;
	LightAmbianceInterpolate[i] = pos[0] * LightAmbianceInterpolate[i];
	LightSpecularInterpolate[i] = pos[1] * LightSpecularInterpolate[i];
	LightDiffuseInterpolate[i] = pos[2] * LightDiffuseInterpolate[i];
      }
    }
  }
  
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_DIRECTION, this->LightDirection);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_EXPONENT, &this->LightExponent);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPOT_CUTOFF, &this->LightCutoff);

  glLightfv(GL_LIGHT0 + this->NumLight, GL_CONSTANT_ATTENUATION, &this->LightAttenConst);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_LINEAR_ATTENUATION, &this->LightAttenLinear);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_QUADRATIC_ATTENUATION, &this->LightAttenQuadratic);

  glLightfv(GL_LIGHT0 + this->NumLight, GL_AMBIENT, LightAmbianceInterpolate);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_SPECULAR, LightSpecularInterpolate);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_DIFFUSE, LightDiffuseInterpolate);
  glLightfv(GL_LIGHT0 + this->NumLight, GL_POSITION, this->LightPosition);
}

void Lighting::FormatAction()
{
  int count = 0;
  int size = vAction.size();

  if(size < 1)
    return;

  float* data = new float[size];

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
  else if(action == "light_interpolate")
  {
    if(size-1 == 0 || (size-1)%13 != 0)
      return;

    int div = size/13;
    
    for(int j = 0; j < div; j++)
    {
      float steps = data[j*13];
      float ctrlpoint1[3];
      float ctrlpoint2[3];
      float ctrlpoint3[3];
      float ctrlpoint4[3];
      
      for(int i = 0; i < 3; i++)
      {
	ctrlpoint1[i] = data[j*13 + 1+i];
	ctrlpoint2[i] = data[j*13 + 4+i];
	ctrlpoint3[i] = data[j*13 + 7+i];
	ctrlpoint4[i] = data[j*13 + 10+i];
      }
      Interpolate::AddCurve(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);
    }

    Interpolate::SetActivated(true);
    Interpolate::SetKeepIncrementing(true);
  }
  delete [] data;
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

void Lighting::AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[])
{
  Interpolate::AddCurve(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);
}
