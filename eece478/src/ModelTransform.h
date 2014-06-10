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
  float                              ModelScale[3] = {1,1,1};
  float                              ModelTranslate[3] = {0,0,0};
  float                              ModelRotate[3] = {0,0,0};
  float                              vModelTranslation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};  ///local transform matrices
  float                              vModelScaling[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float                              vModelRotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float                              vModelAllTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  float                              vModelLookat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};  
  float                              vModelParentTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};  ///parent transform matrix
  float                              vModelCombinedTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
  vector<TransformQueue>             vTransformQueue;
  void                               PutInTransformQueue(int, float[]);
  float                              vWorldtoCamTransform[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};   ///stores world to camera transformation
  int                                TransformMode = 0;
 public:
                                     ModelTransform();
  void                               ApplyScale(float scale[]);
  void                               ApplyRotate(float rotate[]);
  void                               ApplyTranslate(float translate[]);
  void                               ApplyDeltaScale(float scale[]);
  void                               ApplyDeltaRotate(float rotate[]);
  void                               ApplyDeltaTranslate(float translate[]);
  void                               ApplyTransform();  ///applies transformations in queue
  void                               InitializeOrientation(float scale[], float rotate[], float translate[]);
  void                               SetParentTransform(float matrix[]);
  void                               GetCombinedTransform(float out[]);  ///returns combined transform of current entity
  void                               GetParentTransform(float out[]);
  void                               GetScale(float out[]);
  void                               GetTranslate(float out[]);
  void                               GetRotate(float out[]);
  void                               SetWorldtoCamTransform(float[]);   ///sets the world to eye transform
  void                               GetWorldtoCamTransform(float[]);  ///gets the world to eye transform
  void                               GetLocalTransform(float out[]);
  void                               InvertTransform();
  void                               SetTransformMode(int);
  void                               SetLookatTransform(float in[]);
};

#endif
