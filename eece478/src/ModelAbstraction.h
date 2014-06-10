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
  vector<ModelAbstraction*>              vChild;
  ModelAbstraction *                     Parent;
  ModelAbstraction *                     pCamera;   ///root node for rendering using world to eye transform from the camera
  ModelAbstraction *                     pLookatTarget;   ///target entity to lookat to
  ModelAbstraction *                     pMoveToTarget;

 public:	
  vector<string>                         vAction;  ///storage for received action
  string                                 Name;  /// storage for model identifier
                                         ModelAbstraction();
  void                                   DrawModel();  ///updates model view transforms and calls implementable draw method
  virtual void                           Draw();  ///implementable draw function
  virtual void                           Action( string input );  ///implementable action function
  virtual void                           FormatAction(){};  ///implementable action formatting
  void                                   AddChild( ModelAbstraction * child );
  void                                   RemoveChild( ModelAbstraction * child );
  void                                   AddParent( ModelAbstraction * parent );
  void                                   RemoveParent();
  void                                   UpdateParentTransform();  ///gets the parent transform if it exists
  void                                   GetWorldToEntityTransform( float out[] );
  void                                   UpdateWorldToCameraTransform();  //updates and gets transforms from world (root node) to camera
  void                                   DrawCascade();  /// draws this and all children entities in this hierarchy
  bool                                   SetLookatTarget( ModelAbstraction * );  ///sets the entity to look at
  void                                   LookAtTarget();  ///rotates to face set lookat target
  bool                                   GetTargetToCurrentTransform( ModelAbstraction * target, float out[] );
  void                                   SetCamera( ModelAbstraction * cam );
  void                                   MoveToTarget();  ///moves to target location
  void                                   SetMoveToTarget( ModelAbstraction * );   ///sets target to move to
};

#endif
