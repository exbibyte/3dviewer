#include "LightingParse.h"
#include "Lighting.h"
#include "ModelData.h"

#include <vector>
#include <iostream>

LightingParse::LightingParse()
{

}

LightingParse::~LightingParse()
{

}

vector<Lighting *> LightingParse::GetLightings(string path)
/**
Parses and returns a camera path
*/
{
  //output vector of curves
  vector<Lighting *> vpLighting;

  //DOM parse
  DOMNode * pDOM = this->GetDOM(path);

  if(pDOM == NULL)
  {
    cout<<"DOM not parsed"<<endl;
    return vpLighting;
  }

  //stores found curves
  vector<DOMNode *> * pvpDOM = new vector<DOMNode *>();

  //find nodes having a curve
  this->FindLighting(pvpDOM, pDOM);

  for(auto i : *pvpDOM)
  {
    Lighting * NewLighting = new Lighting;
    string actiondata;
    for(auto j : i->Children)
    {
      if(j->Type == "name")
      {
	NewLighting->Name = j->Data;
      }
      else
      {
	//set other lighting properties using Lighting's action parsing
	actiondata = j->Type + " " + j->Data;
	NewLighting->Action(actiondata); 
      }
    }
    vpLighting.push_back(NewLighting);  
    NewLighting = NULL;
  }

  return vpLighting;
}

void LightingParse::FindLighting(vector<DOMNode *> * pvpDOM, DOMNode * node)
{
  if(node->Type == "lighting")
  {
    pvpDOM->push_back(node);
  }

  for(auto i : node->Children)
  {
    this->FindLighting(pvpDOM, i);
  }
}
