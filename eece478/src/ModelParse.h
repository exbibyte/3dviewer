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

///parses model input file and returns a model entity
class ModelParse
{
 private:
  bool                          bEmpty;
  ///container to hold parsed data types such as vertices, textures, triangles, normals, and model name
  vector< ModelData * >         vModelData; 

 public:
                                ModelParse();
				~ModelParse();
  ModelEntity *                 GetEntity(string path);  ///factory function to generate model entity from input model file
};

#endif
