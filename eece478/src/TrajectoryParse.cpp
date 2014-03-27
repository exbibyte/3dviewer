#include "TrajectoryParse.h"
#include "CurveData.h"
#include "ModelData.h"

#include <vector>
#include <iostream>

TrajectoryParse::TrajectoryParse()
{

}

TrajectoryParse::~TrajectoryParse()
{

}

vector<CurvePath *> TrajectoryParse::GetTrajectories(string path)
/**
Parses and returns a camera path
*/
{
  //output vector of curves
  vector<CurvePath *> vpCurvePath;

  //DOM parse
  DOMNode * pDOM = this->GetDOM(path);

  if(pDOM == NULL)
  {
    cout<<"DOM not parsed"<<endl;
    return vpCurvePath;
  }

  //stores found curves
  vector<DOMNode *> * pvpDOM = new vector<DOMNode *>();

  //find nodes having a curve
  this->FindCurve(pvpDOM, pDOM);

  for(auto i : *pvpDOM)
  {
    CurvePath * NewCurvePath = new CurvePath;
    for(auto j : i->Children)
    {
      if(j->Type == "NAME")
      {
	NewCurvePath->Name = j->Data;
      }
      else if(j->Type == "DATA")
      {
	string curvecontrol = j->Data;

	//creates a container for bezier curve data
	CurveData * pCurveData = new CurveData();
	
	// call derived ModelData classes to format and save data
	pCurveData->SetData(curvecontrol); 

	cout<<"curve control: "<<curvecontrol<<endl;
	
	//creates a curve path with given control points
	this->InitializeCurve(NewCurvePath, pCurveData);
	vpCurvePath.push_back(NewCurvePath);  

	delete pCurveData;
	pCurveData = NULL;
	NewCurvePath = NULL;
      }
    }
  }

  return vpCurvePath;
}

void TrajectoryParse::InitializeCurve(CurvePath * pCurve, CurveData * pCurveData)
{
  for(auto i : pCurveData->vCurveControl)
  {
    int steps = std::get<TCURVECONTROL_STEP>(i);
    
    float ctrlpoint1[3];
    float ctrlpoint2[3];
    float ctrlpoint3[3];
    float ctrlpoint4[3];
    
    ctrlpoint1[0] = std::get<TCURVECONTROL_PT1_X>(i);
    ctrlpoint1[1] = std::get<TCURVECONTROL_PT1_Y>(i);
    ctrlpoint1[2] = std::get<TCURVECONTROL_PT1_Z>(i);

    ctrlpoint2[0] = std::get<TCURVECONTROL_PT2_X>(i);
    ctrlpoint2[1] = std::get<TCURVECONTROL_PT2_Y>(i);
    ctrlpoint2[2] = std::get<TCURVECONTROL_PT2_Z>(i);

    ctrlpoint3[0] = std::get<TCURVECONTROL_PT3_X>(i);
    ctrlpoint3[1] = std::get<TCURVECONTROL_PT3_Y>(i);
    ctrlpoint3[2] = std::get<TCURVECONTROL_PT3_Z>(i);

    ctrlpoint4[0] = std::get<TCURVECONTROL_PT4_X>(i);
    ctrlpoint4[1] = std::get<TCURVECONTROL_PT4_Y>(i);
    ctrlpoint4[2] = std::get<TCURVECONTROL_PT4_Z>(i);

    pCurve->AddCurve(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);
  }
}

void TrajectoryParse::FindCurve(vector<DOMNode *> * pvpDOM, DOMNode * node)
{
  if(node->Type == "CURVE")
  {
    pvpDOM->push_back(node);
  }

  for(auto i : node->Children)
  {
    this->FindCurve(pvpDOM, i);
  }
}
