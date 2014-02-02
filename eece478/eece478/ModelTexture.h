#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

#define TTEXTURE_ID 0
#define TTEXTURE_NAME 1

using namespace std;

typedef tuple<int, string> tTexture;

class ModelTexture: ModelData
{
 public:
  ModelTexture();
  vector<tTexture> vTexture;
  void FormatData();
};

#endif
