#include <tuple>
#include <cmath>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

#include "ModelTransform.h"

using namespace std;

ModelTransform::ModelTransform()
{

}

void ModelTransform::ApplyTransform()
{
  float data[3];

  for(auto i : vTransformQueue)
  {

    for(int j = 0; j < 3; j++)
      data[j] = std::get<TRANSFORMQUEUE_DATA>(i)[j];

    //translate
    if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_TRANSLATE)
    {
      //current implementation uses absolute translate instead
      glPushMatrix();     
        glLoadIdentity();
	//delta translate
	glTranslatef(data[0], data[1], data[2]);
	//load current transform
	glMultMatrixf(this->vModelTranslation);
	//save transform
	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelTranslation);
      glPopMatrix();
    }

    //translate absolute
    else if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_TRANSLATE_ABS)
    {
      glPushMatrix();     
        glLoadIdentity();
	glTranslatef(data[0], data[1], data[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelTranslation);
      glPopMatrix();
    }

    //rotate
    else if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_ROTATE)
    {
      //curent implementation uses rotate absolute instead

      //start of object rotation transform
      glPushMatrix();    
        glLoadIdentity();
    	//2nd, apply additional delta transform
        glRotatef(abs(data[0]),data[0],0,0);
    	glRotatef(abs(data[1]),0,data[1],0);
    	glRotatef(abs(data[2]),0,0,data[2]);
    	//1st, apply old rotation transform
    	glMultMatrixf(this->vModelRotation);
    	//save the new rotation transform
    	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelRotation);
      glPopMatrix();
    }    

    //rotate absolute
    else if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_ROTATE_ABS)
    {
      //start of object rotation transform
      glPushMatrix();    
        glLoadIdentity();
        glRotatef(abs(data[0]),data[0],0,0);
    	glRotatef(abs(data[1]),0,data[1],0);
    	glRotatef(abs(data[2]),0,data[2],0);
    	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelRotation);
      glPopMatrix();
    }

    //scale
    else if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_SCALE)
    {
      //curent implementation uses absolute scaling

      float DeltaScale[3];
      for(int k = 0; k < 3; k++)
      {
	DeltaScale[k] = 1+data[k];
	DeltaScale[k] = DeltaScale[k]<0? 0: DeltaScale[k];
      }
		
      //start of object scaling transform
      glPushMatrix();     
        glLoadIdentity();
	//2nd, apply delta scaling
	glScalef(DeltaScale[0],DeltaScale[1],DeltaScale[2]);
	//1st, apply old scaling transform
	glMultMatrixf(this->vModelScaling);
	//lastly, save the new scaling transform
	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelScaling);
      glPopMatrix();
    }     

    //scale absolute
    else if(std::get<TRANSFORMQUEUE_TYPE>(i) == TRANSFORMTYPE_SCALE_ABS)
    {
      float DeltaScale[3];
      for(int k = 0; k < 3; k++)
      {
	DeltaScale[k] = data[k];
	DeltaScale[k] = DeltaScale[k]<0? 0: DeltaScale[k];
      }
		
      //start of object scaling transform
      glPushMatrix();     
        glLoadIdentity();
	//apply scaling
	glScalef(DeltaScale[0],DeltaScale[1],DeltaScale[2]);
	//lastly, save the new scaling transform
	glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelScaling);
      glPopMatrix();
    }     

    //clean up data in queue
    delete [] std::get<TRANSFORMQUEUE_DATA>(i);
  }
  this->vTransformQueue.clear();

  //combine transformations
  glPushMatrix();     
    glLoadIdentity();
    //lastly, apply local transform
    glMultMatrixf(this->vModelTranslation);
    glMultMatrixf(this->vModelRotation);
    glMultMatrixf(this->vModelScaling);  

    //save local transformation
    glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelAllTransform);

  glPopMatrix();
  
  glLoadIdentity();
  //apply parent transform
  glMultMatrixf(vModelParentTransform); 
  //apply local transform
  glMultMatrixf(vModelAllTransform);   
  //save this combined transform
  glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelCombinedTransform);


  glLoadIdentity();  
  //apply world to eye transform
  glMultMatrixf(this->vWorldToEyeTransform);
  //apply combined world to entity transformation
  glMultMatrixf(this->vModelCombinedTransform);
}

void ModelTransform::ApplyDeltaScale(float scale[])
{
  for(int i = 0; i < 3; i++)
  {
    this->ModelScale[i] += scale[i];
    if(this->ModelScale[i] < 0)
      this->ModelScale[i] = 0;
  }

  //uses absolute scaling
  this->PutInTransformQueue(TRANSFORMTYPE_SCALE_ABS, this->ModelScale);
  // this->PutInTransformQueue(TRANSFORMTYPE_SCALE, scale);
}

void ModelTransform::ApplyScale(float scale[])
{
 for(int i = 0; i < 3; i++)
  {
    this->ModelScale[i] = scale[i];
    if(this->ModelScale[i] < 0)
      this->ModelScale[i] = 0;
  }

  this->PutInTransformQueue(TRANSFORMTYPE_SCALE_ABS, this->ModelScale);
}

void ModelTransform::ApplyDeltaRotate(float rotate[])
{
  for(int i = 0; i < 3; i++)
    this->ModelRotate[i] += rotate[i];
 
  //uses absolute rotate
  this->PutInTransformQueue(TRANSFORMTYPE_ROTATE_ABS, this->ModelRotate);

  // this->PutInTransformQueue(TRANSFORMTYPE_ROTATE, this->ModelRotate);
}

void ModelTransform::ApplyRotate(float rotate[])
{
  for(int i = 0; i < 3; i++)
    this->ModelRotate[i] = rotate[i];

  this->PutInTransformQueue(TRANSFORMTYPE_ROTATE_ABS, this->ModelRotate);
}

void ModelTransform::ApplyDeltaTranslate(float translate[])
{
 for(int i = 0; i < 3; i++)
    this->ModelTranslate[i] += translate[i];

 //uses absolute translate
  this->PutInTransformQueue(TRANSFORMTYPE_TRANSLATE_ABS, this->ModelTranslate); 
 // this->PutInTransformQueue(TRANSFORMTYPE_TRANSLATE, this->ModelTranslate);
}

void ModelTransform::ApplyTranslate(float translate[])
{
  for(int i = 0; i < 3; i++)
    this->ModelTranslate[i] = translate[i];

  this->PutInTransformQueue(TRANSFORMTYPE_TRANSLATE_ABS, this->ModelTranslate);
}

void ModelTransform::PutInTransformQueue(int type, float input [])
{
  TransformQueue a;
  float * data = new float[3];
  std::get<TRANSFORMQUEUE_TYPE>(a) = type;
  for(int i = 0; i < 3; i++)
  {
    data[i] = input[i];
  }
  std::get<TRANSFORMQUEUE_DATA>(a) = data;
  data = NULL;
  this->vTransformQueue.push_back(a);
}

void ModelTransform::InitializeOrientation(float scale[], float rotate[], float translate[])
{
  for(int i = 0; i < 3; i++)
  {
    this->ModelRotate[i] = rotate[i];
    this->ModelTranslate[i] = translate[i];
    this->ModelScale[i] = scale[i];
  }

  this->ApplyScale(scale);
  this->ApplyRotate(rotate);
  this->ApplyTranslate(translate);
}

void ModelTransform::SetParentTransform(float matrix[])
{
  for(int i = 0; i < 16; i++)
  {
    this->vModelParentTransform[i] = matrix[i];
  }
}

void ModelTransform::GetCombinedTransform(float out[])
{
  for(int i = 0; i < 16; i++)
    out[i] = this->vModelCombinedTransform[i];
}

void ModelTransform::GetParentTransform(float out[])
{
  for(int i = 0; i < 16; i++)
    out[i] = this->vModelParentTransform[i];
}

void ModelTransform::GetScale(float out[])
{
  for(int i = 0; i < 3; i++)
    out[i] = this->ModelScale[i];
}

void ModelTransform::GetTranslate(float out[])
{
  for(int i = 0; i < 3; i++)
    out[i] = this->ModelTranslate[i];
}

void ModelTransform::GetRotate(float out[])
{
  for(int i = 0; i < 3; i++)
    out[i] = this->ModelRotate[i];
}

void ModelTransform::SetWorldToEyeTransform(float in[])
{
  for(int i = 0; i < 16; i++)
    this->vWorldToEyeTransform[i] = in[i];
}

void ModelTransform::GetWorldToEyeTransform(float out[])
{
  for(int i = 0; i < 16; i++)
    out[i] = this->vWorldToEyeTransform[i];
}

void ModelTransform::GetLocalTransform(float out[])
{
  for(int i = 0; i < 16; i++)
    out[i] = this->vModelAllTransform[i];
}
