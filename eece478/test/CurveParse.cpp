#include "TrajectoryParse.h"
#include <iostream>

#define DEBUG

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout<<"need trajectory file"<<endl;
  }

  TrajectoryParse parser;
  
  vector<CurvePath *> vCurve = parser.GetTrajectories(argv[1]);
  
  cout<<"number of curves: "<<vCurve.size()<<endl;

  cout<<"current position: "<<endl;
  for(auto i : vCurve)
  {
    i->Increment();
    i->PrintPosition();
  }
}
