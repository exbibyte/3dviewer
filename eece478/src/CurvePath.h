#ifndef CURVEPATH_H
#define CURVEPATH_H

#include "ParametricCurve.h"

#include <vector>

using namespace std;

class CurvePath
{
 private:

  vector<ParametricCurve*>::iterator itCurve;
  int CurveIndex;

  ///stores bezier curves to travel through
  vector<ParametricCurve*> vpParametricCurve;

  /// stores position of current step
  float Position[3];

 public:
  CurvePath();
  ~CurvePath();
  
  /// adds a bezier curve to the existing queue of curves
  void AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[]);
  
  /// go to the next step of the curve
  void Increment();

  /// draws the current position as a point
  void Draw();

  void PrintPosition();
};

#endif
