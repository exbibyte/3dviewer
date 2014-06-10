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
  bool                             bEmpty;
  vector< ModelData * >            vModelData;   ///container to hold parsed data types
  void                             FindCurve( vector< DOMNode * > * pvpDOM, DOMNode * node );  ///helper function to find all curves in DOM
  void                             InitializeCurve(CurvePath * pCurve, CurveData * pCurveData);  ///helper function to intialize curves to control points
 public:
                                   TrajectoryParse();
				   ~TrajectoryParse();
  vector<CurvePath *>              GetTrajectories(string path);  ///factory function to generate CurvePath entities from input Trajectory file
};

#endif
