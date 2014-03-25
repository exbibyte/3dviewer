#ifndef CURVEDATA_H
#define CURVEDATA_H

#include "ModelData.h"

#include <vector>
#include <tuple>

typedef tuple<int, float,float,float, float,float,float, float,float,float, float,float,float> tCurveControl;

#define TCURVECONTROL_STEP 0
#define TCURVECONTROL_PT1_X 1
#define TCURVECONTROL_PT1_Y 2
#define TCURVECONTROL_PT1_Z 3
#define TCURVECONTROL_PT2_X 4
#define TCURVECONTROL_PT2_Y 5
#define TCURVECONTROL_PT2_Z 6
#define TCURVECONTROL_PT3_X 7
#define TCURVECONTROL_PT3_Y 8
#define TCURVECONTROL_PT3_Z 9
#define TCURVECONTROL_PT4_X 10
#define TCURVECONTROL_PT4_Y 11
#define TCURVECONTROL_PT4_Z 12

class CurveData : public ModelData
{
 public:
  vector<tCurveControl> vCurveControl;
  CurveData();
  void FormatData(); 
};

#endif
