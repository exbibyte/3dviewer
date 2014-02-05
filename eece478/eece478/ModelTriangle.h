#ifndef MODELTRIANGLE_H
#define MODELTRIANGLE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

///access index of data
#define TTRIANGLE_ID 0
#define TTRIANGLE_VEC1ID 1
#define TTRIANGLE_VEC2ID 2
#define TTRIANGLE_VEC3ID 3
#define TTRIANGLE_NORMID 4
#define TTRIANGLE_TEXTID 5
#define TTRIANGLE_TEXT1 6
#define TTRIANGLE_TEXT2 7
#define TTRIANGLE_TEXT3 8
#define TTRIANGLE_TEXT4 9
#define TTRIANGLE_TEXT5 10
#define TTRIANGLE_TEXT6 11

using namespace std;

///tuple data definition
typedef tuple<int, int,int,int, int, int, float,float,float,float,float,float> tTriangle;

///container for triangle data
class ModelTriangle: ModelData
{
 public:
  ModelTriangle();
  ///container for formatted triangle data
  vector<tTriangle> vTriangle;
  ///formats triangle data
  void FormatData();
};

#endif
