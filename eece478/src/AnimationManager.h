#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "DOMNode.h"
#include "Clock.h"
#include "ModelAbstraction.h"
#include "AnimationParse.h"
#include "ModelPool.h"

#include <vector>
#include <string>

using namespace std;

/// manages models based on clock trigger and parsed animation DOM tree
class AnimationManager : public Clock, public ModelPool
{
 private:
  /// storage for animation
  vector<tAnimation> vAnimation;

 public:

  AnimationManager();
  ~AnimationManager();

  /// adds animation
  void AddAnimation(tAnimation animation);
  
  /// removes animations according to matching animation name
  bool RemoveAnimation(tAnimation animation);

  /// gets animation from matching name
  tAnimation GetAnimation(string name);

  /// implement function to update models based on clock trigger
  void TickAction(string a);
};

#endif
