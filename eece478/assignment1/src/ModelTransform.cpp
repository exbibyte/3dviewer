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
      //start of object rotation transform
      glPushMatrix();    
        glLoadIdentity();
    	//2nd, apply additional delta transform
        glRotatef(abs(data[0]),data[0],0,0);
    	glRotatef(abs(data[1]),0,data[1],0);
    	glRotatef(abs(data[2]),0,data[2],0);
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
    glMultMatrixf(this->vModelTranslation);
    glMultMatrixf(this->vModelRotation);
    glMultMatrixf(this->vModelScaling);  
    glGetFloatv(GL_MODELVIEW_MATRIX,this->vModelAllTransform);
  glPopMatrix();
  
  glMultMatrixf(vModelAllTransform);  
}

void ModelTransform::ApplyDeltaScale(float scale[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_SCALE, scale);
}

void ModelTransform::ApplyScale(float scale[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_SCALE_ABS, scale);
}

void ModelTransform::ApplyDeltaRotate(float rotate[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_ROTATE, rotate);
}

void ModelTransform::ApplyRotate(float rotate[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_ROTATE_ABS, rotate);
}

void ModelTransform::ApplyDeltaTranslate(float translate[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_TRANSLATE, translate);
}

void ModelTransform::ApplyTranslate(float translate[])
{
  this->PutInTransformQueue(TRANSFORMTYPE_TRANSLATE_ABS, translate);
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
  this->ApplyScale(scale);
  this->ApplyRotate(rotate);
  this->ApplyTranslate(translate);
}
