#ifndef MODELNAME_H
#define MODELNAME_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<string> tName;

class ModelName: ModelData
{
 public:
  ModelName();
  vector<tName> vName;
  void FormatData();
};

#endif
