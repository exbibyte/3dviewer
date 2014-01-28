#ifndef MODELVERTICE_H
#define MODELVERTICE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<double,double,double> tVertice;

class ModelVertice: ModelData
{
 public:
  ModelVertice();
  vector<tVertice> vVertice;
  void FormatData();
};

ModelVertice::ModelVertice()
{
  this->mType = VERTICE;
  this->mBeginTag = "<vertice>";
  this->mEndTag = "</vertice>";
}

void ModelVertice::FormatData()	
/** implemented formating for vertice */
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tVertice NewData = std::make_tuple(atof((*it).c_str()),atof((*(it+1)).c_str()),atof((*(it+2)).c_str()));
    this->vVertice.push_back(NewData);
    it += 2;
  }
  
  //check saved model data
  for(auto j : this->vVertice)
  {
    cout<<"tuple data: "<<std::get<0>(j)<<", "<<std::get<1>(j)<<", "<<std::get<2>(j)<<endl;
  }
}

#endif
