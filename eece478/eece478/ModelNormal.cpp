#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include "ModelNormal.h"

using namespace std;

ModelNormal::ModelNormal()
{
  this->mType = NORMAL;
  this->mBeginTag = "<normals>";
  this->mEndTag = "</normals>";
}

void ModelNormal::FormatData()	
/** 
implemented formating for normals
*/
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tNormal NewData = std::make_tuple(i, atof((*it).c_str()), atof((*(it+1)).c_str()), atof((*(it+2)).c_str()) );
    this->vNormal.push_back(NewData);
    it += 2;
    i++;
  }

#ifdef DEBUG   
  //check saved model data
  for(auto j : this->vNormal)
  {
    cout<<"tuple data: "<<std::get<TNORMAL_X>(j)<<", "<<std::get<TNORMAL_Y>(j)<<", "<<std::get<TNORMAL_Z>(j)<<endl;
  }
#endif
}
