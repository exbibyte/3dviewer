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
  
  for(auto i : this->vAnimation)
  {
    //compare time
    if(std::get<TANIMATION_TIME>(i) <= this->GetTime())
    {
      cout<<this->GetTime()<<" s"<<endl;

      //get the right model
      ModelAbstraction * match = this->GetModel(std::get<TANIMATION_SUBJECT>(i));
      if(match != NULL)
      {
	actiondata = std::get<TANIMATION_ACTION>(i) + " " + std::get<TANIMATION_EXTRA>(i);
	//send data to model
	match->Action(actiondata);
      }
    }
  }
}
