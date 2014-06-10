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
  vector<ModelData*>                     vModelData;   ///container to hold parsed data types
  void                                   FindLighting(vector<DOMNode *> * pvpDOM, DOMNode * node);   ///helper function to find all lightings in DOM
 public:
                                         LightingParse();
					 ~LightingParse();
  vector<Lighting*>                      GetLightings(string path);   ///factory function to generate lighting entities from input lighting file
};

#endif
