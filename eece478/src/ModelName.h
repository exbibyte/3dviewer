#ifndef MODELNAME_H
#define MODELNAME_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>
#include <string>

///access index of tuple
#define TNAME_ID 0;
#define TNAME_NAME 1;

using namespace std;

///tuple definition
typedef tuple<int,string> tName;

///container for model name
class ModelName: ModelData
{
 public:
                ModelName();
  vector<tName> vName; ///formatted data
  void          FormatData();  ///saves parsed data to tuple
};

#endif
