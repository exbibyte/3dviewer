#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "DOMNode.h"
#include "Clock.h"
#include "ModelAbstraction.h"
#include "AnimationParse.h"

#include <vector>
#include <string>

using namespace std;

/// manages models based on clock trigger and parsed animation DOM tree
class AnimationManager : public Clock
{
 private:
  /// storage for animation
  vector<tAnimation> vAnimation;

  /// storage for managed models
  vector<ModelAbstraction *> vpModel;
 public:

  AnimationManager();
  ~AnimationManager();

  /// adds animation
  void AddAnimation(tAnimation animation);
  
  /// removes animations according to matching animation name
  bool RemoveAnimation(tAnimation animation);

  /// gets animation from matching name
  tAnimation GetAnimation(string name);

  /// gets model from matching name
  ModelAbstraction * GetModel(string name);

  /// add model to be managed
  void AddModel(ModelAbstraction * model);

  /// implement function to update models based on clock trigger
  void TickAction(string a);
};

#endif
