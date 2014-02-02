#ifndef MODELVERTICE_H
#define MODELVERTICE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>
#include <string>

#define TVERTICE_ID 0
#define TVERTICE_X 1
#define TVERTICE_Y 2
#define TVERTICE_Z 3

using namespace std;

typedef tuple<int, float,float,float> tVertice;

class ModelVertice: ModelData
{
 public:
  ModelVertice();
  vector<tVertice> vVertice;
  void FormatData();
  /* void GetData(string query, void* output, int& count); */
};

#endif
