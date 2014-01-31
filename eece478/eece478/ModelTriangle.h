#ifndef MODELTRIANGLE_H
#define MODELTRIANGLE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<int,int,int, int, int, float,float,float,float,float,float> tTriangle;

class ModelTriangle: ModelData
{
 public:
  ModelTriangle();
  vector<tTriangle> vTriangle;
  void FormatData();
};

#endif
