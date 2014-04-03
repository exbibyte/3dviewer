#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "ParametricCurve.h"

#include <vector>

using namespace std;

class Interpolate
{
 private:

  vector<ParametricCurve*>::iterator itCurve;
  int CurveIndex;

  ///stores bezier curves to travel through
  vector<ParametricCurve*> vpParametricCurve;

  /// stores position of current step
  float Position[3];

  bool bKeepIncrementing;

 public:
  Interpolate();
  ~Interpolate();
  
  /// adds a bezier curve to the existing queue of curves
  void AddCurve(int steps, float ctrlpoint1[], float ctrlpoint2[], float ctrlpoint3[], float ctrlpoint4[]);
  
  /// go to the next step of the curve
  void Increment();

  void PrintPosition();

  /// gets current state of incrementing or not
  bool GetKeepIncrementing();

  /// sets to incrementing or not
  bool SetKeepIncrementing(bool val);

  ///gets the current interpolation
  void GetPosition(float out[]);
};

#endif
