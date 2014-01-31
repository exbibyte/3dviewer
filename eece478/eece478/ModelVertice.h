#ifndef MODELVERTICE_H
#define MODELVERTICE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>
#include <string>

using namespace std;

typedef tuple<float,float,float> tVertice;

class ModelVertice: ModelData
{
 public:
  ModelVertice();
  vector<tVertice> vVertice;
  void FormatData();
  /* void GetData(string query, void* output, int& count); */
};

#endif
