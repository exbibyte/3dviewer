#ifndef MODELPARSE_H
#define MODELPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "ModelData.h"
#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"
#include "ModelEntity.h"

using namespace std;

// this class generates an entity for an input model file path

class ModelParse
{
 private:
  bool bEmpty;
  vector<ModelData*> vModelData; // container to hold parsed data types such as vertices, textures, triangles, normals, and model name

 public:
  ModelParse();
  ~ModelParse();
  ModelEntity * GetEntity(string path); //generator of an entity from input model file path
  
};

#endif
