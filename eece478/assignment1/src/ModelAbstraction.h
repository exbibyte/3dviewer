#ifndef MODELABSTRACTION_H
#define MODELABSTRACTION_H

#include "ModelEntity.h"
#include "ModelTransform.h"

class ModelAbstraction : public ModelTransform, public ModelEntity
{
 public:	
  ModelAbstraction();

  ///updates model view and draws model
  void DrawModel();

};

#endif
