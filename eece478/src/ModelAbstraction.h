#ifndef MODELABSTRACTION_H
#define MODELABSTRACTION_H

#include <vector>

#include "ModelTransform.h"

using namespace std;

///provides ability to attach entities in a hierarchy and inherits entity transforms from ModelTransform
class ModelAbstraction : public ModelTransform
{
 private:
  ///storage for child and parent entities used for transforms
  vector<ModelAbstraction*> vChild;
  vector<ModelAbstraction*> vParent;

 public:	

  string Name;

  ModelAbstraction();

  ///updates model view transforms and calls implementable draw method
  void DrawModel();
  
  ///implementable draw function
  virtual void Draw();

  ///implementable action function
  virtual void Action(string input);

  void AddChild(ModelAbstraction* child);
  void RemoveChild(ModelAbstraction* child);
  void AddParent(ModelAbstraction* parent);
  void RemoveParent(ModelAbstraction* parent);

  ///gets the parent transform if it exists
  void GetParentTransform();

  /// draws this and all children entities in this hierarchy
  void DrawCascade();
};

#endif
