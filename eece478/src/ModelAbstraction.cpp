#include "ModelAbstraction.h"
#include "ModelTransform.h"
#include "MatrixMath.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "MatrixMath.h"

using namespace std;

ModelAbstraction::ModelAbstraction()
{
  this->pAlignTarget = NULL;
  this->pCamera = NULL;
}

void ModelAbstraction::DrawModel()
{
  //grabs world to eye transform from camera
  float worldtoeye[16];
  float worldtoeyeInv[16];
  if(this->pCamera != NULL)
  {
    this->pCamera->GetWorldtoCamTransform(worldtoeye);
    // MatrixMath::PrintMat4x4(worldtoeye);
    
    //saves world to eye transform
    this->SetWorldtoCamTransform(worldtoeye);
  }
  
  //grabs parent transform
  this->UpdateParentTransform();

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
  // cout<<this->Name<<" received action trigger:"<<input<<endl;

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
  else if(actiontype == "transform_addchild")
  {
    //add a child model
    if(this->vAction.size() < 2)
    {
      return;
    }

    //combine str if spaced name was separated
    string combinestr;
    for(int i = 1; i < this->vAction.size(); i++)
    {
      combinestr += this->vAction.at(i);
    }

    cout<<"finding model: "<<combinestr<<endl;
    ModelAbstraction * model = this->GetModel(combinestr);
    if(model != NULL)
    {
      cout<<"model found"<<endl;
      this->AddChild(model);
    }
  }
  else if(actiontype == "transform_addparent")
  {
    //add a child model
    if(this->vAction.size() < 2)
    {
      return;
    }

    //combine str if spaced name was separated
    string combinestr;
    for(int i = 1; i < this->vAction.size(); i++)
    {
      combinestr += this->vAction.at(i);
    }

    cout<<"finding model: "<<combinestr<<endl;
    ModelAbstraction * model = this->GetModel(combinestr);
    if(model != NULL)
    {
      cout<<"model found"<<endl;
      this->AddParent(model);
    }
  }
  else if(actiontype == "transform_delta_translate")
  {
    //translate model
    if(this->vAction.size() < 4)
    {
      return;
    }    
    float nums[4];
    for(int i = 1; i < 4; i++)
    {
      nums[i-1] = atof(this->vAction.at(i).c_str());
    }
    this->ApplyDeltaTranslate(nums);
  }
  else if(actiontype == "transform_align_to_target")
  {
    //aligns to target entity's orientation
    if(this->vAction.size() < 2)
    {
      return;
    }    
    string targetname = this->vAction[1];
    this->SetAlignTarget(targetname);
  }
  else
  {
    //call implementable method in derived class
    this->FormatAction();
  }
  //clear the action
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

void ModelAbstraction::UpdateParentTransform()
{
  //pick the 1st parent for now
  if(vParent.empty() == true)
    return;

  ModelAbstraction * parent = vParent.at(0);

  float ParentTransform[16]; 
  parent->GetCombinedTransform(ParentTransform); 
  this->SetParentTransform(ParentTransform);
}

void ModelAbstraction::GetWorldToEntityTransform(float entitytoworld[])
{
  //search for root node
  bool foundroot = false;
  ModelAbstraction * current = this;
  vector<ModelAbstraction *> sequence;
  
  sequence.push_back(current);

  while(foundroot == false)
  {
    if(current->vParent.empty() == true)
    {
      //found
      foundroot = true;
    }  
    else
    {
      //save current node to list and continue search
      current = current->vParent[0];
      sequence.push_back(current);
    }
  } 

  current = NULL;

  //get transformations from starting node to root node
  float temp[16];
  float temp2[16];
  MatrixMath::GetMat4x4Identity(entitytoworld);
  for(int i = 0; i < sequence.size(); i++)
  {
    sequence[i]->ApplyTransform();
    sequence[i]->GetLocalTransform(temp);
    //concatenate transforms
    MatrixMath::Mat4x4Mult4x4(entitytoworld, temp, temp2);
    for(int j = 0; j < 16; j++)
      entitytoworld[j] = temp2[j];
  }
}

void ModelAbstraction::UpdateWorldToCameraTransform()
{
  if(this->pCamera == NULL)
    return;
  
  float transform[16];
  this->pCamera->GetWorldToEntityTransform(transform);
  this->pCamera->SetWorldtoCamTransform(transform);
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

  this->GetAlignTargetOrientation();
}

void ModelAbstraction::ConvertTransform(float target[16], float reference[16], float out[16])
{
  //get inverse of reference matrix
  float refinverse[16];
  MatrixMath::InvertMatrix(reference, refinverse);

  float unnormalized[16];
  
  //pre multiply target transform by inverse of reference transform
  MatrixMath::Mat4x4Mult4x4(target, refinverse, unnormalized);

  MatrixMath::Mat4x4Normalize(unnormalized, out);  
}

bool ModelAbstraction::SetAlignTarget(string target)
{
  this->pAlignTarget = this->GetModel(target);

  if(this->pAlignTarget == NULL)
    return false;

  return true;
}

bool ModelAbstraction::GetAlignTargetOrientation()
{
  if(this->pAlignTarget == NULL)
    return false;
 
  float TargetParentTransform[16];
  // this->pAlignTarget->GetParentTransform(TargetParentTransform);
  this->pAlignTarget->GetCombinedTransform(TargetParentTransform);

  float ReferenceParentTransform[16];
  // this->GetParentTransform(ReferenceParentTransform);
  this->GetCombinedTransform(ReferenceParentTransform);

  float RelativeTransform[16];

  this->ConvertTransform(TargetParentTransform, ReferenceParentTransform, RelativeTransform);

  float TargetScale[4];
  this->pAlignTarget->GetScale(TargetScale);
  TargetScale[3] = 0;

  float TargetTranslate[4];
  this->pAlignTarget->GetTranslate(TargetTranslate);
  cout<<"target local translation: ";
  for(int i = 0; i < 3; i++)
    cout<<TargetTranslate[i]<<",";
  cout<<endl;
  
  TargetTranslate[3] = 1;

  float TargetRotate[4];
  this->pAlignTarget->GetRotate(TargetRotate);
  TargetRotate[3] = 0;
  
  float RelativeScale[4];
  float RelativeTranslate[4];
  float RelativeRotate[4];

  cout<<"parent transform: "<<endl;
  MatrixMath::PrintMat4x4(TargetParentTransform);

  cout<<"relative transform: "<<endl;
  MatrixMath::PrintMat4x4(RelativeTransform);

  MatrixMath::Mat4x4Mult4x1(TargetScale, RelativeTransform, RelativeScale);
  MatrixMath::Mat4x4Mult4x1(TargetTranslate, RelativeTransform, RelativeTranslate);
  MatrixMath::Mat4x4Mult4x1(TargetRotate, RelativeTransform, RelativeRotate);

  float RelativeTranslateNorm[16];
  MatrixMath::Mat4x1Normalize(RelativeTranslate,RelativeTranslateNorm);  

  cout<<"input target Coordinates: "<<TargetTranslate[0]<<","<<TargetTranslate[1]<<","<<TargetTranslate[2]<<endl;

  cout<<"relative Coordinates: "<<RelativeTranslateNorm[0]<<","<<RelativeTranslateNorm[1]<<","<<RelativeTranslateNorm[2]<<","<<RelativeTranslateNorm[3]<<endl;

  return true;
}

void ModelAbstraction::SetCamera(ModelAbstraction * cam)
{
  this->pCamera = cam;
}
