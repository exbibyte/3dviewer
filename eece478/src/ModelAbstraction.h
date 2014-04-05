#ifndef MODELABSTRACTION_H
#define MODELABSTRACTION_H

#include <vector>
#include <string>

#include "ModelTransform.h"
#include "ModelPool.h"

using namespace std;

///provides ability to attach entities in a hierarchy and inherits entity transforms from ModelTransform and ability to access other models from ModelPool
class ModelAbstraction : public ModelTransform, public ModelPool
{
 private:
  ///storage for child and parent entities used for transforms
  vector<ModelAbstraction*> vChild;
  vector<ModelAbstraction*> vParent;
  
  ///root node for rendering using world to eye transform from the camera
  ModelAbstraction* pCamera;

  ///target entity to lookat to
  ModelAbstraction* pLookatTarget;

 public:	

  ///storage for received action
  vector<string> vAction;

  /// storage for model identifier
  string Name;

  ModelAbstraction();

  ///updates model view transforms and calls implementable draw method
  void DrawModel();
  
  ///implementable draw function
  virtual void Draw();

  ///implementable action function
  virtual void Action(string input);

  ///implementable action formatting
  virtual void FormatAction(){};

  void AddChild(ModelAbstraction* child);
  void RemoveChild(ModelAbstraction* child);
  void AddParent(ModelAbstraction* parent);
  void RemoveParent(ModelAbstraction* parent);

  ///gets the parent transform if it exists
  void UpdateParentTransform();

  //updates and gets transforms from world (root node) to current node
  void GetWorldToEntityTransform(float out[]);

  //updates and gets transforms from world (root node) to camera
  void UpdateWorldToCameraTransform();

  /// draws this and all children entities in this hierarchy
  void DrawCascade();

  ///sets the entity to look at
  bool SetLookatTarget(string target);

  ///rotates to face set lookat target
  void LookAtTarget();

  ///gets the target orientation with respect to this transformation
  bool GetTargetToCurrentTransform(ModelAbstraction * target, float out[]);

  ///sets the camera node to apply world to eye transform to this entity
  void SetCamera(ModelAbstraction * cam);
};

#endif
