#ifndef MODELABSTRACTION_H
#define MODELABSTRACTION_H

#include <vector>

#include "ModelEntity.h"
#include "ModelTransform.h"

using namespace std;

class ModelAbstraction : public ModelTransform, public ModelEntity
{
 private:
  ///storage for child and parent entities used for transforms
  vector<ModelAbstraction*> vChild;
  vector<ModelAbstraction*> vParent;

 public:	
  ModelAbstraction();

  ///updates model view and draws model
  void DrawModel();

  void AddChild(ModelAbstraction* child);
  void RemoveChild(ModelAbstraction* child);
  void AddParent(ModelAbstraction* parent);
  void RemoveParent(ModelAbstraction* parent);

  ///gets the parent transform if it exists
  void GetParentTransform();
};

#endif
