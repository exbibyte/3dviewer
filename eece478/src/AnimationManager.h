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
  vector<tAnimation>                   vAnimation;
 public:
                                       AnimationManager();
                                       ~AnimationManager();
  void                                 AddAnimation(tAnimation animation);   /// adds animation
  bool                                 RemoveAnimation(tAnimation animation);   /// removes animations according to matching animation name
  tAnimation                           GetAnimation(string name);   /// gets animation from matching name
  void                                 TickAction(string a);   /// implement function to update models based on clock trigger
};

#endif
