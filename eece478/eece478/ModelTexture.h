#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<string> tTexture;

class ModelTexture: ModelData
{
 public:
  ModelTexture();
  vector<tTexture> vTexture;
  void FormatData();
};

ModelTexture::ModelTexture()
{
  this->mType = TEXTURE;
  this->mBeginTag = "<texture>";
  this->mEndTag = "</texture>";
}

void ModelTexture::FormatData()	
/** implemented formating for texture */
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tTexture NewData = std::make_tuple((string)*it);
    this->vTexture.push_back(NewData);
  }
  
  //check saved model data
  for(auto j : this->vTexture)
  {
    cout<<"tuple data: "<<std::get<0>(j)<<endl;
  }
}

#endif
