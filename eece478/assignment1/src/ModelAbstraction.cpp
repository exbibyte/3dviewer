#include "ModelAbstraction.h"
#include "ModelEntity.h"
#include "ModelTransform.h"

ModelAbstraction::ModelAbstraction()
{

}

void ModelAbstraction::DrawModel()
{
  //grabs parent transform
  this->GetParentTransform();

  //update model view transformations
  this->ApplyTransform();

  //draw model
  this->Draw();
}

void ModelAbstraction::AddChild(ModelAbstraction* child)
{
  for(auto i : this->vChild)
  {
    if(i == child)
    {
      return;
    }
  }

  this->vChild.push_back(child);
  child->AddParent(this);
}

void ModelAbstraction::RemoveChild(ModelAbstraction* child)
{
  auto i = this->vChild.begin();
  
  while (i != this->vChild.end()) 
  {
    if(*i == child)
    {
      child->RemoveParent(this);
      this->vChild.erase(i);
      return;
    }
  }
}

void ModelAbstraction::AddParent(ModelAbstraction* parent)
{
  for(auto i : this->vParent)
  {
    if(i == parent)
    {
      return;
    }
  }

  this->vParent.push_back(parent);
  parent->AddChild(this);
}

void ModelAbstraction::RemoveParent(ModelAbstraction* parent)
{
  auto i = this->vParent.begin();
  
  while (i != this->vParent.end()) 
  {
    if(*i == parent)
    {
      parent->RemoveChild(this);
      this->vParent.erase(i);
      return;
    }
  }
}

void ModelAbstraction::GetParentTransform()
{
  //pick the 1st parent for now
  if(vParent.empty() == true)
    return;

  ModelAbstraction * parent = vParent.at(0);
  float * ParentTransform = parent->GetCombinedTransform(); 
  this->SetParentTransform(ParentTransform);
  delete [] ParentTransform;
  ParentTransform = NULL;
}
