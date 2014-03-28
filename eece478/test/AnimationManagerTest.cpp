#include <iostream>
#include <cmath>

#include "ModelAbstraction.h"
#include "AnimationManager.h"
#include "AnimationParse.h"
#include "TrajectoryParse.h"
#include "CurvePath.h"

using namespace std;

int main(int argc, char** argv)
{
  
  if(argc < 3)
  { 
    cout<<"not enough arguments: <curve path> <animation path>"<<endl;
    return -1;
  }

  TrajectoryParse curveparser;

  vector<CurvePath *> vpCurve = curveparser.GetTrajectories(argv[1]);

  AnimationParse animationparser;

  vector<tAnimation> vAnimation = animationparser.GetAnimations(argv[2]);  

  //create animation manager 
  AnimationManager manager;

  //test model adding
  for(auto i : vpCurve)
  {
    manager.AddModel(i);
  }

  ModelAbstraction * querymodel = manager.GetModel("curve1");

  if(querymodel == NULL)
    cout<<"model not found"<<endl;
  else
    cout<<querymodel->Name<<" found"<<endl;
  
  //test animation adding
  for(auto i : vAnimation)
  {
    manager.AddAnimation(i);
  }

  tAnimation queryanimation = manager.GetAnimation("CurveRun2");
  
  cout<<std::get<TANIMATION_NAME>(queryanimation)<<", "<<std::get<TANIMATION_TIME>(queryanimation)<<endl;

  return 0;
}
