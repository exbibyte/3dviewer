#ifndef MODELNORMAL_H
#define MODELNORMAL_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<float,float,float> tNormal;

class ModelNormal: ModelData
{
 public:
  ModelNormal();
  vector<tNormal> vNormal;
  void FormatData();
};

#endif
