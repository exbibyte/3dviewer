#ifndef LIGHTING_H
#define LIGHTING_H

#include <string> 

#include "ModelAbstraction.h"

using namespace std;

///inherits transformation functionality from ModelAbstraction
class Lighting: public ModelAbstraction 
{
 private:
  ///storage for this light id
  int NumLight;
  ///storage for light type
  string LightType;
  ///determines whether this light is usable or not
  bool bFunctional;

  ///storage for lighting parameters
  float LightAmbiance[4] = {0,0,0,1};
  float LightDiffuse[4] = {1,1,1,1};
  float LightSpecular[4] = {1,1,1,1};
  float LightPosition[4] = {0,0,0,1};

  float LightDirection[4] = {0,0,1,0};
  float LightExponent = 0;
  float LightCutoff = 180;

  float LightAttenConst = 1;
  float LightAttenLinear = 0;
  float LightAttenQuadratic = 0;

 public:
  ///storage for current total number of lights
  static int TotalNumLight;

  Lighting();
  void TurnOn();
  void TurnOff();
  ///sets the lighting parameters
  void SetLightParam(float amb[], float spec[], float dif[], float pos[]);
  void SetLightParamSpot(float dir[], float exp, float cutoff);
  void SetLightAttenuation(string type, float att);
  
  void SetLightAmbient(float[]);
  void SetLightSpecular(float[]);
  void SetLightDiffuse(float[]);
  void SetLightPosition(float[]);
  void SetLightDirection(float[]);
  void SetLightExponent(float[]);
  void SetLightCutoff(float[]);

  ///sets lighting type (optional)
  void SetType(string type);
  string GetType();

  ///draws the lighting
  void Draw();

  ///processes additional commannds
  void FormatAction();

  void FormatData();

};

#endif
