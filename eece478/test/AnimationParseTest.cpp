#include <iostream>

#include "DOMNode.h"
#include "AnimationParse.h"
#include "DOMParse.h"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout<<"need DOM file"<<endl;
  }

  AnimationParse parser;

  vector<tAnimation> vAnimation = parser.GetAnimations(argv[1]);

  cout<<"number of animations: "<<vAnimation.size()<<endl;

  for(auto i : vAnimation)
  {
    cout<<std::get<TANIMATION_NAME>(i)<<", "<<std::get<TANIMATION_TIME>(i)<<", "<<std::get<TANIMATION_ACTION>(i)<<", "<<std::get<TANIMATION_SUBJECT>(i)<<", "<<std::get<TANIMATION_EXTRA>(i)<<endl;
  }

  return 0;
}
