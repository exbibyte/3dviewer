#include <string>
#include <tuple>
#include <iostream>
#include <vector>
#include "ModelTexture.h"

using namespace std;

ModelTexture::ModelTexture()
{
  this->mType = TEXTURE;
  this->mBeginTag = "<textures>";
  this->mEndTag = "</textures>";
}

void ModelTexture::FormatData()	
/** 
implemented formating for texture 
*/
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tTexture NewData = std::make_tuple(i, (string)*it);
    this->vTexture.push_back(NewData);
    i++;
  }

#ifdef DEBUG   
  //check saved model data
  for(auto j : this->vTexture)
  {
    cout<<"tuple data: "<<std::get<TTEXTURE_NAME>(j)<<endl;
  }
#endif
}
