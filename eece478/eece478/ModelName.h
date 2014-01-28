#ifndef MODELNAME_H
#define MODELNAME_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<string> tName;

class ModelName: ModelData
{
 public:
  ModelName();
  vector<tName> vName;
  void FormatData();
};

ModelName::ModelName()
{
  this->mType = NAME;
  this->mBeginTag = "<name>";
  this->mEndTag = "</name>";
}

void ModelName::FormatData()	
/** implemented formating for vertice */
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tName NewData = std::make_tuple(*it);
    this->vName.push_back(NewData);
  }
  
  //check saved model data
  for(auto j : this->vName)
  {
    cout<<"tuple data: "<<std::get<0>(j)<<endl;
  }
}

#endif
