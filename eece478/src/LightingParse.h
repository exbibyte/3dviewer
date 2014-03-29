#ifndef LIGHTINGPARSE_H
#define LIGHTINGPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "DOMParse.h"
#include "DOMNode.h"
#include "ModelData.h"

using namespace std;

class Lighting;

///parses Lighting input file and returns lighting entities
class LightingParse : public DOMParse
{
 private:

  ///container to hold parsed data types
  vector<ModelData*> vModelData; 

  ///helper function to find all lightings in DOM
  void FindLighting(vector<DOMNode *> * pvpDOM, DOMNode * node);

 public:
  LightingParse();
  ~LightingParse();

  ///factory function to generate lighting entities from input lighting file
  vector<Lighting*> GetLightings(string path);
};

#endif
