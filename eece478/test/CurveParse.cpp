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

  if(vCurve.empty())
    return -1;

  cout<<"number of curves: "<<vCurve.size()<<endl;

  cout<<"current position: "<<endl;

  int curvecount = 0;

  for(auto i : vCurve)
  {
    cout<<"curve number: "<<curvecount<<endl;
    for(int j = 0; j < 45; j++)
    {
      i->Increment();
      i->PrintPosition();
    }
    curvecount++;
    break;
  }
}
