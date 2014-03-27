#ifndef ANIMATIONPARSE_H
#define ANIMATIONPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "DOMParse.h"
#include "DOMNode.h"

///accesoor index for animation information
#define TANIMATION_NAME 0
#define TANIMATION_TIME 1
#define TANIMATION_ACTION 2
#define TANIMATION_SUBJECT 3
#define TANIMATION_EXTRA 4

/// storage for animation information
typedef tuple<string,float,string,string,string> tAnimation;

using namespace std;

///parses Animation input file and returns animation entities
class AnimationParse : public DOMParse
{
 private:

  ///helper function to find all animations in DOM
  void FindAnimation(vector<DOMNode *> * pvpDOM, DOMNode * node);

 public:
  AnimationParse();
  ~AnimationParse();

  ///factory function to generate animation entities from input animation file
  vector<tAnimation> GetAnimations(string path);
};

#endif
