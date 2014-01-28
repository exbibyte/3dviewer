#include "ModelParse.h"
#include "ModelTexture.h"
#include "ModelData.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

ModelParse::ModelParse(string path)
{
  ModelTexture * cModelTexture = new ModelTexture();

  vector<ModelData*> vModelData;
  vModelData.push_back((ModelData*)cModelTexture);

  ifstream ifs;
  stringstream Ss;

  ifs.open(path.c_str(), ifstream::in);

  string line;
  int LineNum = 0;

  //remove lines with #comments
  while (getline(ifs, line)) 
  {    
    size_t found = line.find("#");
    if(found == std::string::npos){
      Ss<<line<<" "; // save to buffer
    }
  }

  //match <tags> and </tags> from ModelData and extract info to ModelData
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
	}
      }
    }
  }

  delete cModelTexture;
}
