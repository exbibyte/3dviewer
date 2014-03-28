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
/**
implemented formating for name
*/
{
  if(this->vDataItem.empty())
  {
    cout<<"warning: a model name was not parsed since it has not enough arugments"<<endl;
    return;
  }

  //combine name strings if the name contains spaces
  string combinedname;
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    combinedname += *it;
  }
  
  //save
  tName NewData = std::make_tuple(0,combinedname);
  this->vName.push_back(NewData);

#ifdef DEBUG 
  //check saved model data
  for(auto j : this->vName)
  {
    cout<<"tuple data: "<<std::get<TNAME_NAME>(j)<<endl;
  }
#endif
}
