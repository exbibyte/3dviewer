#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

///access index of data
#define TTEXTURE_ID 0
#define TTEXTURE_NAME 1

using namespace std;

///tuple definition
typedef tuple<int, string> tTexture;

///container for model texture
class ModelTexture: ModelData
{
 public:
  ModelTexture();
  ///container for model texture
  vector<tTexture> vTexture;
  ///formats texture names 
  void FormatData();
};

#endif
