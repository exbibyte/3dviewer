#ifndef TRAJECTORYPARSE_H
#define TRAJECTORYPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "CurvePath.h"
#include "CurveData.h"
#include "ModelData.h"
#include "DOMParse.h"
#include "DOMNode.h"

using namespace std;

///parses Trajectory input file and returns CurvePath entities
class TrajectoryParse : public DOMParse
{
 private:
  bool bEmpty;
  ///container to hold parsed data types
  vector<ModelData*> vModelData; 

  ///helper function to find all curves in DOM
  void FindCurve(vector<DOMNode *> * pvpDOM, DOMNode * node);

  ///helper function to intialize curves to control points
  void InitializeCurve(CurvePath * pCurve, CurveData * pCurveData);

 public:
  TrajectoryParse();
  ~TrajectoryParse();

  ///factory function to generate CurvePath entities from input Trajectory file
  vector<CurvePath *> GetTrajectories(string path);
};

#endif
