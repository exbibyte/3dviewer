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

using namespace std;

ModelParse::ModelParse()
{
}

ModelParse::~ModelParse()
{
  for(auto i : vModelData)
  {
    delete i;
  }
}

ModelEntity * ModelParse::GetEntity(string path)
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

  ModelName * cModelName = new ModelName();
  ModelTexture * cModelTexture = new ModelTexture();
  ModelVertice * cModelVertice = new ModelVertice();
  ModelNormal * cModelNormal = new ModelNormal();
  ModelTriangle * cModelTriangle = new ModelTriangle();

  vModelData.push_back((ModelData*)cModelName);
  vModelData.push_back((ModelData*)cModelTexture);
  vModelData.push_back((ModelData*)cModelVertice);
  vModelData.push_back((ModelData*)cModelNormal);
  vModelData.push_back((ModelData*)cModelTriangle);

  string line;
  int LineNum = 0;

  //remove lines with #comments
  while (getline(ifs, line)) 
  {    
    size_t found = line.find("#");
    if(found == std::string::npos){
      Ss<<line<<" "; // save remaining to a single lined buffer
    }
  }

  this->bEmpty = true;

  //find <tags> and </tags> defined in ModelData and extract info to ModelData
  line.clear();
  while (getline(Ss, line)) 
  { 
    for(auto i : vModelData)
    {
      size_t FoundStartTag = line.find(i->mBeginTag);
      if(FoundStartTag != std::string::npos){
	size_t FoundEndTag = line.find(i->mEndTag);
	if(FoundEndTag != std::string::npos){
	  //when found begin and end tags, extract data
	  string SubString = line.substr(FoundStartTag + i->mBeginTag.length(),FoundEndTag-(FoundStartTag + i->mBeginTag.length()));
	  i->SetData(SubString); // format and set data to ModelData object

	  this->bEmpty = false;
	}
      }
    }
  }

  if(this->bEmpty)
  {
    return NULL;
  }

  //save to model entity
  ModelEntity * output = new ModelEntity();
  output->cModelName = cModelName;
  output->cModelTexture = cModelTexture;
  output->cModelVertice = cModelVertice;
  output->cModelNormal = cModelNormal;
  output->cModelTriangle = cModelTriangle;
  
  cModelName = NULL;
  cModelTexture = NULL;
  cModelVertice = NULL;
  cModelNormal = NULL;
  cModelTriangle = NULL;

  vModelData.clear();

  return output;
}
