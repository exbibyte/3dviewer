#include "AnimationManager.h"

#include <vector>
#include <string>

using namespace std;

AnimationManager::AnimationManager()
{
  this->pDOM = NULL;
}

AnimationManager::~AnimationManager()
{
  vpModel.clear();
}

void AnimationManager::SetAnimationDOM(DOMNode * node)
{
  this->pDOM = node;
}

void AnimationManager::SetModels(ModelAbstraction * model)
{
  vpModel.push_back(model);
}

void AnimationManager::TickAction(string a)
{
  // add stuff here to update models based on clock update
  // can call ModelAbstraction->Action method to update model
}
