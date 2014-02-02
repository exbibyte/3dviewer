#ifndef MODELTRIANGLE_H
#define MODELTRIANGLE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

#define TTRIANGLE_ID 0
#define TTRIANGLE_VECX 1
#define TTRIANGLE_VECY 2
#define TTRIANGLE_VECZ 3
#define TTRIANGLE_NORM 4
#define TTRIANGLE_TEXT 5
#define TTRIANGLE_TEXT1 6
#define TTRIANGLE_TEXT2 7
#define TTRIANGLE_TEXT3 8
#define TTRIANGLE_TEXT4 9
#define TTRIANGLE_TEXT5 10
#define TTRIANGLE_TEXT6 11

using namespace std;

typedef tuple<int, int,int,int, int, int, float,float,float,float,float,float> tTriangle;

class ModelTriangle: ModelData
{
 public:
  ModelTriangle();
  vector<tTriangle> vTriangle;
  void FormatData();
};

#endif
