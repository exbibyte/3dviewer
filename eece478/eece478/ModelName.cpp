#include <string>
#include <vector>
#include <tuple>
#include <iostream>

#include "ModelName.h"

using namespace std;

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
    tName NewData = std::make_tuple(i,*it);
    this->vName.push_back(NewData);
    i++;
  }
  
#ifdef DEBUG 
  //check saved model data
  for(auto j : this->vName)
  {
    cout<<"tuple data: "<<std::get<TNAME_NAME>(j)<<endl;
  }
#endif
}
