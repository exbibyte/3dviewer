#ifndef CURVEPATH_H
#define CURVEPATH_H

#include "ParametricCurve.h"
#include "ModelAbstraction.h"
#include "Interpolate.h"

#include <vector>

using namespace std;

class CurvePath : private Interpolate, public ModelAbstraction
{
 private:

 public:
  CurvePath();
  ~CurvePath();

  /// draws the current position as a point
  void Draw();

  /// implemented method derived from ModelAbstraction to react to animation events
  void FormatAction();

  /// redirects this to Iterpolate class
  void AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[]);

};

#endif
