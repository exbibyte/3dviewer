#ifndef MODELNORMAL_H
#define MODELNORMAL_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

///access index to tuple
#define TNORMAL_ID 0
#define TNORMAL_X 1
#define TNORMAL_Y 2
#define TNORMAL_Z 3

using namespace std;

///tuple definition
typedef tuple<int, float,float,float> tNormal;

///container for triangle normals
class ModelNormal: ModelData
{
 public:
  ModelNormal();
  ///container for formatted data
  vector<tNormal> vNormal;
  ///formats data
  void FormatData();
};

#endif
