#include "CurveData.h"

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

CurveData::CurveData()
{
  this->mType = CURVE;
  //ignore these tags for current version of implementation
  this->mBeginTag = "<curve>";
  this->mEndTag = "</curve>";
}

void CurveData::FormatData()
{
  if(this->vDataItem.size()%13 != 0)
  {
    cout<<"number of Curve control point arguments not valid"<<endl;
    return;
  }

  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); )
  {  
    tCurveControl NewControlPoint;

    std::get<TCURVECONTROL_STEP>(NewControlPoint) = atoi((*it).c_str());
    std::get<TCURVECONTROL_PT1_X>(NewControlPoint) = atof((*(it+1)).c_str());
    std::get<TCURVECONTROL_PT1_Y>(NewControlPoint) = atof((*(it+2)).c_str());
    std::get<TCURVECONTROL_PT1_Z>(NewControlPoint) = atof((*(it+3)).c_str());
    std::get<TCURVECONTROL_PT2_X>(NewControlPoint) = atof((*(it+4)).c_str());
    std::get<TCURVECONTROL_PT2_Y>(NewControlPoint) = atof((*(it+5)).c_str());
    std::get<TCURVECONTROL_PT2_Z>(NewControlPoint) = atof((*(it+6)).c_str());
    std::get<TCURVECONTROL_PT3_X>(NewControlPoint) = atof((*(it+7)).c_str());
    std::get<TCURVECONTROL_PT3_Y>(NewControlPoint) = atof((*(it+8)).c_str());
    std::get<TCURVECONTROL_PT3_Z>(NewControlPoint) = atof((*(it+9)).c_str());
    std::get<TCURVECONTROL_PT4_X>(NewControlPoint) = atof((*(it+10)).c_str());
    std::get<TCURVECONTROL_PT4_Y>(NewControlPoint) = atof((*(it+11)).c_str());
    std::get<TCURVECONTROL_PT4_Z>(NewControlPoint) = atof((*(it+12)).c_str());
    
    this->vCurveControl.push_back(NewControlPoint);
  
    it += 13;
  }

#ifdef DEBUG 
  //check saved model data
  for(auto j : this->vCurveControl)
  {
    cout<<"tuple data: "<<std::get<TCURVECONTROL_STEP>(j)<<", "<<std::get<TCURVECONTROL_PT1_Z>(j)<<", "<<std::get<TCURVECONTROL_PT4_Z>(j)<<endl;
  }
#endif
}

void CurveData::ClearData()
{
  this->vDataItem.clear();
  this->vCurveControl.clear();
}
