#include "ModelAbstraction.h"
#include "ModelTransform.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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

void ModelAbstraction::Draw()
{
}

void ModelAbstraction::Action(string input)
{
  cout<<this->Name<<" received action trigger:"<<input<<endl;

  stringstream Ss;
  Ss.str(input);
  string temp;

  //separate items to vector
  while (Ss>>temp)
  {
    this->vAction.push_back(temp);
    temp.clear();
  }

  string actiontype = "";

  int count = 0;
  int actionsize = this->vAction.size();

  for(auto i : this->vAction)
  {
    if(count == 0)
    {
      actiontype = i;
      break;
    }
  }

  if(actiontype == "draw")
  {
    this->DrawModel();
  }

  this->FormatAction();

  this->vAction.clear();
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

void ModelAbstraction::DrawCascade()
{
  //update and draw current entity
  this->DrawModel();
  
  //do the same for children 
  for(auto i : this->vChild)
  {
    i->DrawCascade();
  }
}
