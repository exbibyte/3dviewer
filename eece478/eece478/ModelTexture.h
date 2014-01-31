#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<string> tTexture;

class ModelTexture: ModelData
{
 public:
  ModelTexture();
  vector<tTexture> vTexture;
  void FormatData();
};

#endif
