#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "DOMNode.h"
#include "Clock.h"
#include "ModelAbstraction.h"

#include <vector>
#include <string>

using namespace std;

/// manages models based on clock trigger and parsed animation DOM tree
class AnimationManager : public Clock
{
 private:
  DOMNode * pDOM;
 public:

  AnimationManager();
  ~AnimationManager();

  /// stores models to be managed
  vector<ModelAbstraction *> vpModel;

  /// sets the parsed DOM tree
  void SetAnimationDOM(DOMNode * node);

  /// add model to be managed
  void SetModels(ModelAbstraction * model);

  /// implement function to update models based on clock trigger
  void TickAction(string a);
};

#endif
