#ifndef MODELABSTRACTION_H
#define MODELABSTRACTION_H

#include <vector>

#include "ModelTransform.h"

using namespace std;

class ModelAbstraction : public ModelTransform
{
 private:
  ///storage for child and parent entities used for transforms
  vector<ModelAbstraction*> vChild;
  vector<ModelAbstraction*> vParent;

 public:	
  ModelAbstraction();

  ///updates model view transforms and calls implementable draw method
  void DrawModel();
  
  ///implementable draw function
  virtual void Draw();

  void AddChild(ModelAbstraction* child);
  void RemoveChild(ModelAbstraction* child);
  void AddParent(ModelAbstraction* parent);
  void RemoveParent(ModelAbstraction* parent);

  ///gets the parent transform if it exists
  void GetParentTransform();

};

#endif
