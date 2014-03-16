#include "ModelAbstraction.h"
#include "ModelEntity.h"
#include "ModelTransform.h"

ModelAbstraction::ModelAbstraction()
{

}

void ModelAbstraction::DrawModel()
{
  //update model view transformations
  this->ApplyTransform();

  //draw model
  this->Draw();
}


