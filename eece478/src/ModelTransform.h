#ifndef MODELORIENTATION_H
#define MODELORIENTATION_H

#include <vector>
#include <tuple>

using namespace std;

///stores transforms to be applied
typedef tuple<int,float*> TransformQueue;

#define TRANSFORMQUEUE_TYPE 0
#define TRANSFORMQUEUE_DATA 1

#define TRANSFORMTYPE_TRANSLATE 0
#define TRANSFORMTYPE_ROTATE 1
#define TRANSFORMTYPE_SCALE 2
#define TRANSFORMTYPE_TRANSLATE_ABS 3
#define TRANSFORMTYPE_ROTATE_ABS 4
#define TRANSFORMTYPE_SCALE_ABS 5

///provides transformation abilities and cascades transform from parent hierarchy
class ModelTransform
{
 private:
  ///initial local model orientation
  float ModelScale[3] = {1,1,1};
  float ModelTranslate[3] = {0,0,0};
  float ModelRotate[3] = {0,0,0};

  ///local transform matrices
  float vModelTranslation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float vModelScaling[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float vModelRotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float vModelAllTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  
  ///parent transform matrix
  float vModelParentTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  float vModelCombinedTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

  vector<TransformQueue> vTransformQueue;

  void PutInTransformQueue(int, float[]);

  ///stores WorldToEyeTransform
  float vWorldToEyeTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

 public:

  ModelTransform();

  ///functions to change orientation
  void ApplyScale(float scale[]);
  void ApplyRotate(float rotate[]);
  void ApplyTranslate(float translate[]);

  void ApplyDeltaScale(float scale[]);
  void ApplyDeltaRotate(float rotate[]);
  void ApplyDeltaTranslate(float translate[]);

  ///applies transformations in queue
  void ApplyTransform();

  ///sets intial model orientation
  void InitializeOrientation(float scale[], float rotate[], float translate[]);
  
  ///sets transform from the parent 
  void SetParentTransform(float matrix[]);

  ///returns combined transform of current entity
  void GetCombinedTransform(float out[]);

  //gets the parent transformation of the current entity
  void GetParentTransform(float out[]);

  void GetScale(float out[]);
  void GetTranslate(float out[]);
  void GetRotate(float out[]);

  ///sets the world to eye transform
  void SetWorldToEyeTransform(float[]);

  ///gets the world to eye transform
  void GetWorldToEyeTransform(float[]);

  ///gets local transform
  void GetLocalTransform(float out[]);
};

#endif
