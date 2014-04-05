#include "ModelAbstraction.h"
#include "ModelTransform.h"
#include "MatrixMath.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cmath>

#include "MatrixMath.h"

using namespace std;

ModelAbstraction::ModelAbstraction()
{
  this->pLookatTarget = NULL;
  this->pCamera = NULL;
  this->Parent = NULL;
}

void ModelAbstraction::DrawModel()
{
  //grabs world to eye transform from camera
  float worldtoeye[16];
  float worldtoeyeInv[16];
  if(this->pCamera != NULL)
  {
    this->pCamera->GetWorldtoCamTransform(worldtoeye);
    
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
  else if(actiontype == "lookat")
  {
    //lookats to target entity's orientation
    if(this->vAction.size() < 2)
    {
      return;
    }    
    string targetname = this->vAction[1];
    this->SetLookatTarget(targetname);
    
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
  if(this->Parent == parent)
  {
    return;
  }
  else
  {
    this->Parent = parent;
  }
}

void ModelAbstraction::RemoveParent(ModelAbstraction* parent)
{
  if(this->Parent == parent)
  {
    this->Parent = NULL;
  }
}

void ModelAbstraction::UpdateParentTransform()
{
  //pick the 1st parent for now
  if(this->Parent == NULL)
    return;

  float ParentTransform[16]; 
  this->Parent->GetCombinedTransform(ParentTransform); 
  this->SetParentTransform(ParentTransform);
}

void ModelAbstraction::GetWorldToEntityTransform(float worldtoentity[])
{
  //search for root node
  bool foundroot = false;
  ModelAbstraction * current = this;
  vector<ModelAbstraction *> sequence;
  
  sequence.push_back(current);

  while(foundroot == false)
  {
    if(current->Parent == NULL)
    {
      //found
      foundroot = true;
    }  
    else
    {
      //save current node to list and continue search
      current = current->Parent;
      sequence.push_back(current);
    }
  } 

  current = NULL;

  //get transformations from starting node to root node
  float temp[16];
  float temp2[16];
  MatrixMath::GetMat4x4Identity(worldtoentity);
  for(int i = 0; i < sequence.size(); i++)
  {
    sequence[i]->InvertTransform();
   
    sequence[i]->ApplyTransform();
    sequence[i]->GetLocalTransform(temp);
    //concatenate transforms
    MatrixMath::Mat4x4Mult4x4(worldtoentity,temp,temp2);
    for(int j = 0; j < 16; j++)
      worldtoentity[j] = temp2[j];
    //invert back
    sequence[i]->InvertTransform();
    sequence[i]->ApplyTransform();
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
  //sets rotation orientation to look at set target
  this->LookAtTarget();

  //update and draw current entity
  this->DrawModel();

  //do the same for children 
  for(auto i : this->vChild)
  {
    i->DrawCascade();
  }
}

bool ModelAbstraction::SetLookatTarget(string target)
{
  this->pLookatTarget = this->GetModel(target);

  if(this->pLookatTarget == NULL)
    return false;

  return true;
}

bool ModelAbstraction::GetTargetToCurrentTransform(ModelAbstraction * target, float out[])
{
  if(target == NULL)
    return false;
 
  float TargetToWorld[16];
  this->pLookatTarget->GetCombinedTransform(TargetToWorld);

  float WorldToCurrent[16];
  this->GetWorldToEntityTransform(WorldToCurrent);

  float TargetToCurrent[16];
  MatrixMath::Mat4x4Mult4x4(WorldToCurrent,TargetToWorld,TargetToCurrent);

  MatrixMath::Mat4x4Normalize(TargetToCurrent, out);

  return true;
}

void ModelAbstraction::SetCamera(ModelAbstraction * cam)
{
  this->pCamera = cam;
}

void ModelAbstraction::LookAtTarget()
{
  if(this->pLookatTarget!=NULL)
  {
    float TargetToCurrent[16];
    //get relative transform to target
    this->GetTargetToCurrentTransform(this->pLookatTarget, TargetToCurrent);
    MatrixMath::PrintMat4x4(TargetToCurrent);

    //get offset to target
    float targetorigin[4] = {0,0,0,1};
    float offset[4];
    MatrixMath::Mat1x4Mult4x4(targetorigin, TargetToCurrent, offset);
    // cout<<"offset:"<<endl;
    // MatrixMath::PrintMat4x1(offset);
    
    //rotate to face target entity
    float rotate[4] = {0,0,0,0};
    if(abs(offset[2])>0.01)
    {
      float ry = atan2(offset[2],offset[0])*180/PI+90;
      float rx = atan2(offset[2],offset[1])*180/PI+90;
      rotate[0] = rx;
      rotate[1] = ry;
    }
    
    // cout<<"rotation:"<<endl;
    // MatrixMath::PrintMat4x1(rotate);

    this->ApplyDeltaRotate(rotate);
    this->ApplyTransform();
  }
}
