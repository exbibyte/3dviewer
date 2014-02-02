#ifndef MODELNAME_H
#define MODELNAME_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

#define TNAME_ID 0;
#define TNAME_NAME 1;

using namespace std;

typedef tuple<int,string> tName;

class ModelName: ModelData
{
 public:
  ModelName();
  vector<tName> vName;
  void FormatData();
};

#endif
