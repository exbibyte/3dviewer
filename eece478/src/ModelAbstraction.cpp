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
  this->pMoveToTarget = NULL;
  this->pCamera = NULL;
  this->Parent = NULL;
}

void ModelAbstraction::DrawModel()
{
  this->MoveToTarget();

  //sets rotation orientation to look at set target
  this->LookAtTarget();

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
  else if(actiontype == "transform_removeparent")
  {
    this->RemoveParent();
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
    
    //combine str if spaced name was separated
    string combinestr;
    for(int i = 1; i < this->vAction.size(); i++)
    {
      combinestr += this->vAction.at(i);
    }    

    ModelAbstraction * model = this->GetModel(combinestr);
    
    //test to see if it's the camera that is being rotated
    if(this == this->pCamera->Parent)
    {
      //set camerarotate to look at things
      this->pCamera->SetLookatTarget(model);
    }
    else
      this->SetLookatTarget(model);
  }
  else if(actiontype == "transform_moveto")
  {
    //lookats to target entity's orientation
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
    ModelAbstraction * model = this->GetModel(combinestr);
    this->SetMoveToTarget(model);
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
  child->Parent = this;
}

void ModelAbstraction::RemoveChild(ModelAbstraction* child)
{
  auto i = this->vChild.begin();
  
  while (i != this->vChild.end()) 
  {
    if(*i == child)
    {
      if(child->Parent == this)
	child->Parent = NULL;

      this->vChild.erase(i);
      return;
    }
  }
}

void ModelAbstraction::AddParent(ModelAbstraction* parent)
{
  if(parent != NULL)
    parent->AddChild(this);
}

void ModelAbstraction::RemoveParent()
{ 
  if(this->Parent != NULL)
  {
    //get world coodinate of the object and save it
    float entitytoworld[16];
    this->GetCombinedTransform(entitytoworld);
    float origin[4] = {0,0,0,1};
    float offset[4];
    MatrixMath::Mat4x4Mult4x1(origin,entitytoworld,offset);
    this->ApplyTranslate(offset);
    // cout<<"offset:"<<endl;
    // MatrixMath::PrintMat4x1(offset);

    //add this to root
    ModelAbstraction * root = this;
    bool foundroot = false;
    while(foundroot == false)
    {
      if(root->Parent == NULL)
	foundroot = true;
      else
	root = root->Parent;

      cout<<root->Name<<endl;
    }

    if(root == this->Parent)
      return;

    ModelAbstraction * oldparent = this->Parent;
    root->AddChild(this);
    oldparent->RemoveChild(this);
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
  //update and draw current entity
  this->DrawModel();

  //do the same for children 
  for(auto i : this->vChild)
  {
    if( i != NULL)
    {
      i->DrawCascade();
    }
  }
}

bool ModelAbstraction::SetLookatTarget(ModelAbstraction * target)
{
  this->pLookatTarget = target;
}

bool ModelAbstraction::GetTargetToCurrentTransform(ModelAbstraction * target, float out[])
{
  if(target == NULL)
    return false;
 
  float TargetToWorldNormScale[16];
  float WorldToCurrentNormScale[16];

  float TargetToWorld[16];
  target->GetCombinedTransform(TargetToWorld);

  //normalize scaling
  MatrixMath::NormalizeScalingMat4x4(TargetToWorld, TargetToWorldNormScale);
 
  //   cout<<"targettoworld:"<<endl;
  //   MatrixMath::PrintMat4x4(TargetToWorldNormScale);
 

  float WorldToCurrent[16];
  this->GetWorldToEntityTransform(WorldToCurrent);

  //normalize scaling
  MatrixMath::NormalizeScalingMat4x4(WorldToCurrent, WorldToCurrentNormScale);
 
  //   cout<<"WorldToCurrent:"<<endl;
  //   MatrixMath::PrintMat4x4(WorldToCurrentNormScale);

  //invert current entity's translation
  float WorldToCurrentNormScaleInvertTranslate[16];
  MatrixMath::InvertTranslateMat4x4(WorldToCurrentNormScale,WorldToCurrentNormScaleInvertTranslate);

  float TargetToCurrent[16];
  //concatenate transforms to get target to current entity's transform
  MatrixMath::Mat4x4Mult4x4(WorldToCurrentNormScaleInvertTranslate,TargetToWorldNormScale,TargetToCurrent);

  //   cout<<"TargetToCurrent_before_normalize:"<<endl;
  //   MatrixMath::PrintMat4x4(TargetToCurrent);

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

    // cout<<"targettocurrent:"<<endl;
    // MatrixMath::PrintMat4x4(TargetToCurrent);

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
      float ry = atan2(offset[2],offset[0])*180/PI + 90;
      float rx = atan2(offset[2],offset[1])*180/PI + 90;
      
      // cout<<"ry: "<<ry<<", rx: "<<rx<<endl;
      if(ry > 180)
	ry = 180 - ry;
      if(rx > 180)
	rx = 180 - rx;

      rotate[0] = rx;
      rotate[1] = ry;
    }
    
    // cout<<"rotation:"<<endl;
    // MatrixMath::PrintMat4x1(rotate);

    //reorient entity's rotation
    this->ApplyDeltaRotate(rotate);
  }
}

void ModelAbstraction::SetMoveToTarget(ModelAbstraction * target)
{
  if(target!=NULL)
  {
    this->RemoveParent();
    this->pMoveToTarget = target;
  }
}
void ModelAbstraction::MoveToTarget()
{
  if(this->pMoveToTarget == NULL)
    return;

  cout<<"running"<<endl;
  float TargetToWorld[16];
  this->pMoveToTarget->GetCombinedTransform(TargetToWorld);
  //get offset to target
  float targetorigin[4] = {0,0,0,1};
  float targetpos[4];
  MatrixMath::Mat4x4Mult4x1(targetorigin, TargetToWorld, targetpos);
  // cout<<"BusShelter world transform"<<endl;
  // MatrixMath::PrintMat4x4(TargetToWorld);

  float CurrentToWorld[16];
  float currentpos[4];
  this->GetCombinedTransform(CurrentToWorld);
  MatrixMath::Mat4x4Mult4x1(targetorigin, CurrentToWorld, currentpos);
  // cout<<"current world transform"<<endl;
  // MatrixMath::PrintMat4x4(CurrentToWorld);
  float offset[3];
  for(int i = 0; i < 3; i++)
  {
    offset[i] = targetpos[i] - currentpos[i];
  }
  
  this->ApplyDeltaTranslate(offset);
}
