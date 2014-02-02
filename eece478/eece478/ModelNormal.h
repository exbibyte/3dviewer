#ifndef MODELNORMAL_H
#define MODELNORMAL_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

#define TNORMAL_ID 0
#define TNORMAL_X 1
#define TNORMAL_Y 2
#define TNORMAL_Z 3

using namespace std;

typedef tuple<int, float,float,float> tNormal;

class ModelNormal: ModelData
{
 public:
  ModelNormal();
  vector<tNormal> vNormal;
  void FormatData();
};

#endif
