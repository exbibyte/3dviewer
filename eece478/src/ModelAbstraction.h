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
  void GetParentTransform();

  /// draws this and all children entities in this hierarchy
  void DrawCascade();
};

#endif
