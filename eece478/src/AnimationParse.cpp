#include "AnimationParse.h"
#include "DOMNode.h"
#include "DOMParse.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <stdlib.h>
#include <string>

using namespace std;

AnimationParse::AnimationParse()
{

}

AnimationParse::~AnimationParse()
{

}

vector<tAnimation> AnimationParse::GetAnimations(string path)
/**
Parses and returns a camera path
*/
{
  //output vector of animation
  vector<tAnimation> vAnimation;

  //DOM parse
  DOMNode * pDOM = this->GetDOM(path);

  if(pDOM == NULL)
  {
    cout<<"DOM not parsed"<<endl;
    return vAnimation;
  }

  //stores found animations
  vector<DOMNode *> * pvpDOM = new vector<DOMNode *>();

  //find nodes having animation
  this->FindAnimation(pvpDOM, pDOM);

  for(auto i : *pvpDOM)
  {
    tAnimation NewAnimation;

    for(auto j : i->Children)
    {
      if(j->Type == "NAME")
      {
	std::get<TANIMATION_NAME>(NewAnimation) = j->Data;
      }
      else if(j->Type == "TIME")
      {
	std::get<TANIMATION_TIME>(NewAnimation) = atof(j->Data.c_str());
      }
      else if(j->Type == "ACTION")
      {
	std::get<TANIMATION_ACTION>(NewAnimation) = j->Data;
      }
      else if(j->Type == "SUBJECT")
      {
	std::get<TANIMATION_SUBJECT>(NewAnimation) = j->Data;
      }
      else if(j->Type == "EXTRA")
      {
	std::get<TANIMATION_EXTRA>(NewAnimation) = j->Data;
      }
    }
    vAnimation.push_back(NewAnimation);
  }
  return vAnimation;
}

void AnimationParse::FindAnimation(vector<DOMNode *> * pvpDOM, DOMNode * node)
{
  if(node->Type == "ANIMATION")
  {
    pvpDOM->push_back(node);
  }

  for(auto i : node->Children)
  {
    this->FindAnimation(pvpDOM, i);
  }
  
  return;
}
