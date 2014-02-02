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

class ModelParse
{
 private:
  bool bEmpty;
  vector<ModelData*> vModelData;

 public:
  //load model and store model info within the class
  ModelParse();
  ~ModelParse();
  ModelEntity * GetEntity(string path);
  
};

#endif
