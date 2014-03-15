#ifndef MODELVERTICE_H
#define MODELVERTICE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>
#include <string>

///access index of data
#define TVERTICE_ID 0
#define TVERTICE_X 1
#define TVERTICE_Y 2
#define TVERTICE_Z 3

using namespace std;

///data tuple definition
typedef tuple<int, float,float,float> tVertice;

///container for vertices data
class ModelVertice: ModelData
{
 public:
  ModelVertice();
  ///container of formatted data
  vector<tVertice> vVertice;
  ///formats vertices
  void FormatData();
};

#endif
