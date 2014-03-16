#ifndef CITYPARSE_H
#define CITYPARSE_H

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "ModelParse.h"
#include "ModelAbstraction.h"

class CityParse
{
 private:
  ModelParse cModelParse; ///factory to generate model
  vector<ModelAbstraction*> vEntity;///temporary storage for produced models

 public:
  CityParse();
  vector<ModelAbstraction*> ParseCity(string path); /// parses city file and returns a vector of entities   
};

#endif
