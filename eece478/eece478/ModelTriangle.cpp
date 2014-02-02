#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include "ModelTriangle.h"

using namespace std;

ModelTriangle::ModelTriangle()
{
  this->mType = TRIANGLE;
  this->mBeginTag = "<triangles>";
  this->mEndTag = "</triangles>";
}

void ModelTriangle::FormatData()	
/** implemented formating for Triangle */
{
  int i = 0;
 
  //convert data to expected format
  for(std::vector<string>::iterator it = this->vDataItem.begin(); it != vDataItem.end(); ++it)
  {
    tTriangle NewData;
    std::get<TTRIANGLE_ID>(NewData) = i;
    std::get<TTRIANGLE_VEC1ID>(NewData) = atoi((*it).c_str());
    std::get<TTRIANGLE_VEC2ID>(NewData) = atoi((*(it+1)).c_str());
    std::get<TTRIANGLE_VEC3ID>(NewData) = atoi((*(it+2)).c_str());

    std::get<TTRIANGLE_NORMID>(NewData) = atoi((*(it+3)).c_str());
    std::get<TTRIANGLE_TEXTID>(NewData) = atoi((*(it+4)).c_str());

    std::get<TTRIANGLE_TEXT1>(NewData) = atof((*(it+5)).c_str());
    std::get<TTRIANGLE_TEXT2>(NewData) = atof((*(it+6)).c_str());
    std::get<TTRIANGLE_TEXT3>(NewData) = atof((*(it+7)).c_str());
    std::get<TTRIANGLE_TEXT4>(NewData) = atof((*(it+8)).c_str());
    std::get<TTRIANGLE_TEXT5>(NewData) = atof((*(it+9)).c_str());
    std::get<TTRIANGLE_TEXT6>(NewData) = atof((*(it+10)).c_str());

    this->vTriangle.push_back(NewData);
    it += 10;
    i++;
  }
  
#ifdef DEBUG 
  //check saved model data
  for(auto j : this->vTriangle)
  {
    cout<<"tuple data: "<<std::get<TTRIANGLE_VEC1ID>(j)<<", "<<std::get<TTRIANGLE_VEC2ID>(j)<<", "<<std::get<TTRIANGLE_VEC3ID>(j)<<", "<<std::get<TTRIANGLE_NORMID>(j)<<", "<<std::get<TTRIANGLE_TEXTID>(j)<<", "<<std::get<TTRIANGLE_TEXT1>(j)<<", "<<std::get<TTRIANGLE_TEXT2>(j)<<", "<<std::get<TTRIANGLE_TEXT3>(j)<<", "<<std::get<TTRIANGLE_TEXT4>(j)<<", "<<std::get<TTRIANGLE_TEXT5>(j)<<", "<<std::get<TTRIANGLE_TEXT6>(j)<<endl;
  }
#endif
}
