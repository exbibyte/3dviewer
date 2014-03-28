#include "AnimationManager.h"
#include "ModelPool.h"

#include <vector>
#include <string>

using namespace std;

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::AddAnimation(tAnimation animation)
{
  this->vAnimation.push_back(animation);
}

bool AnimationManager::RemoveAnimation(tAnimation animation)
{
  string name = std::get<TANIMATION_NAME>(animation);

  auto it = this->vAnimation.begin();

  bool removed = false;

  while(it != this->vAnimation.end())
  {
    if(std::get<TANIMATION_NAME>(*it) == name)
    {
      this->vAnimation.erase(it);
      removed = true;
    }
    else
    {
      it++;
    }
  }
  
  return removed;
}

tAnimation AnimationManager::GetAnimation(string name)
{
  tAnimation output;
  for(auto i : this->vAnimation)
  {
    if(std::get<TANIMATION_NAME>(i) == name)
    {   
      output = i;
      break;
    }
  }
  return output;
}

void AnimationManager::TickAction(string a)
{
  // add stuff here to update models based on clock update
  // can call ModelAbstraction->Action method to update model

  string actiondata = "";

  vector<tAnimation>::iterator it = this->vAnimation.begin();
  
  cout<<this->GetTime()<<" s"<<endl;

  while(it != this->vAnimation.end())
  {
    //compare time
    if(std::get<TANIMATION_TIME>(*it) <= this->GetTime())
    {
      //get the right model
      ModelAbstraction * match = this->GetModel(std::get<TANIMATION_SUBJECT>(*it));
      if(match != NULL)
      {
	actiondata = std::get<TANIMATION_ACTION>(*it) + " " + std::get<TANIMATION_EXTRA>(*it);
	//send data to model
	match->Action(actiondata);
      }
      this->vAnimation.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
