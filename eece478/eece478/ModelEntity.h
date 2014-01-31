#ifndef MODEL_ENTITY_H
#define MODEL_ENTITY_H

#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

class ModelEntity{
public:
  int vNumVertice;
  ModelName * cModelName;
  ModelTexture * cModelTexture;
  ModelVertice * cModelVertice;
  ModelNormal * cModelNormal;
  ModelTriangle * cModelTriangle;
  void GetVertices(float*& data, int& num);
};

#endif
