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


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

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

  //grabs world to eye transform from camera
  float worldtoeye[16];
  float worldtoeyeInv[16];
  if(this->pCamera != NULL)
  {
    this->pCamera->GetWorldtoCamTransform(worldtoeye);
    
    //saves world to eye transform
    this->SetWorldtoCamTransform(worldtoeye);
  }
 
  this->MoveToTarget();

  //sets rotation orientation to look at set target
  this->LookAtTarget();
 
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

    // cout<<"finding model: "<<combinestr<<endl;
    ModelAbstraction * model = this->GetModel(combinestr);
    if(model != NULL)
    {
      // cout<<"model found"<<endl;
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

    // cout<<"finding model: "<<combinestr<<endl;
    ModelAbstraction * model = this->GetModel(combinestr);
    if(model != NULL)
    {
      // cout<<"model found"<<endl;
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
  else if(actiontype == "transform_abs_translate")
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
    this->ApplyTranslate(nums);
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
    
    this->SetLookatTarget(model);
  }
  else if(actiontype == "transform_moveto")
  {
    //move to target entity
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
  else if(actiontype == "transform_moveto_detach")
  {
    //stop moving to a target entity
    this->SetMoveToTarget(NULL);
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
  if(child == NULL)
    return;

  //check if it's already a child
  for(auto i : this->vChild)
  {
    if(i == child)
    {
      return;
    }
  }

  //get world coodinate of the current object
  float entitypos[4];
  if(this->Parent == NULL)
  {
    this->GetTranslate(entitypos);
  }
  else
  {
    float entitytoworld[16];
    this->GetCombinedTransform(entitytoworld);
    float origin[4] = {0,0,0,1};
    MatrixMath::Mat4x4Mult4x1(origin,entitytoworld,entitypos);
  }

  //get world coodinate of the target object
  float targetpos[4];  
  if(child->Parent == NULL)
  {
    child->GetTranslate(targetpos);
  }
  else
  {
    float targettoworld[16];
    child->GetCombinedTransform(targettoworld);
    float origin[4] = {0,0,0,1};
    MatrixMath::Mat4x4Mult4x1(origin,targettoworld,targetpos);
  }
  
  //save relative position into target child
  float offset[4];
  for(int i = 0; i < 3; i++)
  {
    offset[i] = targetpos[i] - entitypos[i];
  }
  
  // cout<<"offset"<<endl;
  // MatrixMath::PrintMat4x1(offset);
 

  ModelAbstraction * temp = child;
  
  //save absolute offset to child
  child->ApplyTranslate(offset);

  //add this child
  this->vChild.push_back(child);

  //remove it from parent
  child->RemoveParent();

  child->Parent = this;
}

void ModelAbstraction::RemoveChild(ModelAbstraction* child)
{
  auto i = this->vChild.begin();
  
  while (i != this->vChild.end()) 
  {
    if(*i == child)
    {
      (*i)->Parent = NULL;
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

    //add this to root world
    ModelAbstraction * root = this;
    bool foundroot = false;
    while(foundroot == false)
    {
      if(root->Parent == NULL)
	foundroot = true;
      else
	root = root->Parent;
    }

    if(root == this->Parent)
      return;

    ModelAbstraction * oldparent = this->Parent;
    root->AddChild(this);
    oldparent->RemoveChild(this);

    this->ApplyTransform();
  }
}

void ModelAbstraction::UpdateParentTransform()
{
  float ParentTransform[16]; 

  if(this->Parent == NULL)
  {
    MatrixMath::GetMat4x4Identity(ParentTransform);
    this->SetParentTransform(ParentTransform);
  }
  else
  {
    this->Parent->GetCombinedTransform(ParentTransform); 
    this->SetParentTransform(ParentTransform);
  }
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

    // //testing
    // sequence[i]->GetLocalTransform(temp);
    // float out[16];
    // float out2[16];
    // MatrixMath::NormalizeScalingMat4x4(temp,out2);
    // MatrixMath::InvertRotateMat4x4(out2,out);
    // MatrixMath::InvertTranslateMat4x4(out,out2);
    // MatrixMath::Mat4x4Mult4x4(worldtoentity,out2,temp2);
    // for(int j = 0; j < 16; j++)
    //   worldtoentity[j] = temp2[j];

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
  if(this->pCamera == NULL || this != this->pCamera)
    return;
  
  float transform[16];
  this->GetCombinedTransform(transform);
  
  float transformtarget[16];
  if(this->pLookatTarget != NULL)
    this->pLookatTarget->GetCombinedTransform(transformtarget);
  else
    MatrixMath::GetMat4x4Identity(transformtarget);

  float cameratransform[16];
  glPushMatrix();    
    glLoadIdentity();
    
    //set camera transform with glulookat
    gluLookAt(transform[12], transform[13], transform[14],
	      transformtarget[12], transformtarget[13], transformtarget[14],
	      0, 1, 0);
    
    glGetFloatv(GL_MODELVIEW_MATRIX, cameratransform);
  glPopMatrix();

  this->pCamera->SetWorldtoCamTransform(cameratransform);
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

  // if(this == this->pCamera)
  // { 
  //   cout<<"targettoworld:"<<endl;
  //   MatrixMath::PrintMat4x4(TargetToWorldNormScale);
  // }

  float WorldToCurrent[16];
  this->GetWorldToEntityTransform(WorldToCurrent);

  //normalize scaling
  MatrixMath::NormalizeScalingMat4x4(WorldToCurrent, WorldToCurrentNormScale);

  // if(this == this->pCamera)
  // {
  //   cout<<"WorldToCurrent:"<<endl;
  //   MatrixMath::PrintMat4x4(WorldToCurrentNormScale);
  // }

  float TargetToCurrent[16];
  //concatenate transforms to get target to current entity's transform
  MatrixMath::Mat4x4Mult4x4(WorldToCurrentNormScale,TargetToWorldNormScale,TargetToCurrent);

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

    // if(this == this->pCamera)
    // {
    //   cout<<"targettocurrent:"<<endl;
    //   MatrixMath::PrintMat4x4(TargetToCurrent);
    // }

    //get offset to target
    float targetorigin[4] = {0,0,0,1};
    float offset[4];
    MatrixMath::Mat1x4Mult4x4(targetorigin, TargetToCurrent, offset);
    // if(this == this->pCamera)
    // {    
    //   cout<<"offset:"<<endl;
    //   MatrixMath::PrintMat4x1(offset);
    // }
    //rotate to face target entity
    float rotate[4] = {0,0,0,0};
    if(abs(offset[2])>0.01)
    {
      float ry;
      float rx;

      ry = -90 + atan2(offset[2],offset[0])*180/PI;
      rx = -90 + atan2(offset[2],offset[1])*180/PI;

      if(ry > 180)
      	ry = ry - 360;
      else if(ry < -180)
      	ry = 360 + ry;

      if(rx > 180)
      	rx = rx - 360;
      else if(rx < -180)
      	rx = 360 + rx;

      rotate[0] = rx;
      rotate[1] = ry;

    }
    
    // if(this == this->pCamera)
    // {
    //   cout<<"rotation:"<<endl;
    //   MatrixMath::PrintMat4x1(rotate);
    // }

    //reorient entity's rotation
    this->SetTransformMode(1);
    this->ApplyDeltaRotate(rotate);
    this->ApplyTransform();
  }
}

void ModelAbstraction::SetMoveToTarget(ModelAbstraction * target)
{
  if(target!=NULL)
  {
    this->RemoveParent();
    this->pMoveToTarget = target;
  }
  else
  {
    this->pMoveToTarget = NULL;
  }
}
void ModelAbstraction::MoveToTarget()
{
  if(this->pMoveToTarget == NULL)
    return;

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

  float fraction[3];

  for(int i = 0; i < 3; i++)
  {
    offset[i] = targetpos[i] - currentpos[i];
    fraction[i] = offset[i]*1/10;
  }

  this->ApplyDeltaTranslate(fraction);
  // this->ApplyDeltaTranslate(offset);
}
