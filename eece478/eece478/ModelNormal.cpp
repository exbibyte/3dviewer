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
/** implemented formating for vertice */
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tNormal NewData = std::make_tuple(atof((*it).c_str()), atof((*(it+1)).c_str()), atof((*(it+2)).c_str()) );
    this->vNormal.push_back(NewData);
    it += 2;
  }

#ifdef DEBUG   
  //check saved model data
  for(auto j : this->vNormal)
  {
    cout<<"tuple data: "<<std::get<0>(j)<<", "<<std::get<1>(j)<<", "<<std::get<2>(j)<<endl;
  }
#endif
}
