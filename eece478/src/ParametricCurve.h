#ifndef PARAMETRICCURVE_H
#define PARAMETRICCURVE_H

///provides ability to trace out position of a cubic bezier curve using forward differencing. Taken from pp.365-367 of Chapter 8 of Advanced 3D Game Programming with DirectX 10.0 by Peter Walsh
class ParametricCurve
{
 private:
  int                   mCurrentStep;
  int                   mTotalStep;
  float                 mControlPoints[4][3];  /// bezier control points
  float                 mPoint[3];
  float                 mDPoint[3];
  float                 mDDPoint[3];
  float                 mDDDPoint[3];
  float                 mBezierBasis[4][4] = {{-1,3,-3,1}, {3,-6,3,0}, {-3,3,0,0}, {1,0,0,0}};  /// bezier basis matrix
  bool                  bStarted;
 public:
                        ParametricCurve();
  void                  SetParameter(int steps, float control1[], float control2[], float control3[], float control4[]);  ///sets control points for the curve
  void                  Increment();
  void                  GetCurrent(float*& out); 
  void                  Start();  ///initialize the curved
  bool                  Done();  ///see if the curve had reached the en
  bool                  Started();
};

#endif
