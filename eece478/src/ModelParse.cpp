#include "ModelParse.h"

#include "ModelData.h"
#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

ModelParse::ModelParse()
{
}

ModelParse::~ModelParse()
/** 
delete any allocated data
*/
{
  for(auto i : vModelData)
  {
    delete i;
  }
}

ModelEntity * ModelParse::GetEntity(string path)
/**
Parses and returns a model entity for the input model file
@param path model file path
@return ModelEntity an entity holding formatted data and also provides methods to draw triangles
*/
{
  ifstream ifs;
  stringstream Ss;

  //open model file
  ifs.open(path.c_str(), ifstream::in);
  if(!ifs.is_open())
  {
    cout<<"error opening file: "<<path<<endl;
    return NULL;
  }

  //creates containers for basic model data
  ModelName * cModelName = new ModelName();
  ModelTexture * cModelTexture = new ModelTexture();
  ModelVertice * cModelVertice = new ModelVertice();
  ModelNormal * cModelNormal = new ModelNormal();
  ModelTriangle * cModelTriangle = new ModelTriangle();

  //prepares to extract data using loop
  vModelData.push_back((ModelData*)cModelName);
  vModelData.push_back((ModelData*)cModelTexture);
  vModelData.push_back((ModelData*)cModelVertice);
  vModelData.push_back((ModelData*)cModelNormal);
  vModelData.push_back((ModelData*)cModelTriangle);

  string line;
  int LineNum = 0;

  //remove parsed lines with #comments
  while (getline(ifs, line)) 
  {    
    size_t found = line.find("#");
    if(found == std::string::npos){
      Ss<<line<<" "; // save remaining lines to a single lined buffer and add space to ensure data separation
    }
  }

  this->bEmpty = true;

  //find <tags> and </tags> defined in ModelData and extract string to ModelData
  line.clear();
  while (getline(Ss, line)) 
  { 
    for(auto i : vModelData)
    {
      size_t FoundStartTag = line.find(i->mBeginTag);
      if(FoundStartTag != std::string::npos)
      {
	size_t FoundEndTag = line.find(i->mEndTag);
	if(FoundEndTag != std::string::npos)
	{
	  //when found begin and end tags, extract string
	  string SubString = line.substr(FoundStartTag + i->mBeginTag.length(),FoundEndTag-(FoundStartTag + i->mBeginTag.length()));
	  i->SetData(SubString); // call derived ModelData classes to format and save data

	  this->bEmpty = false;
	}
      }
    }
  }

  //if can't find tags, return
  if(this->bEmpty)
  {
    return NULL;
  }

  //creates a model entity and save parsed data
  ModelEntity * output = new ModelEntity();
  output->Initialize(cModelName, cModelTexture, cModelVertice, cModelNormal, cModelTriangle);

  //truncate path to the model folder path
  string Folder = "/";
  unsigned found = path.rfind(Folder);
  if(found!=std::string::npos)
  {
    path = path.substr(0,found+1); 
  }
  output->ModelFilePath = path;

  //null pointers
  cModelName = NULL;
  cModelTexture = NULL;
  cModelVertice = NULL;
  cModelNormal = NULL;
  cModelTriangle = NULL;
  vModelData.clear();

  return output;
}


