#include <tuple>
#include <iostream>

#include "ModelEntity.h"
#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

void ModelEntity::GetVertices(float*& data, int& num)
/**
return:
data: 1D array of vertice data
num: array size
*/
{
  this->vNumVertice = (this->cModelVertice->vVertice.size());
  num = this->vNumVertice*3;

#ifdef DEBUG
  cout<<"vertex count"<<num<<endl; 
#endif

  data = new float[num];

  for(auto i : this->cModelVertice->vVertice)
  {
    *data = std::get<0>(i);
    data++;
    *data = std::get<1>(i);
    data++;
    *data = std::get<2>(i);
    data++;
  }
  data -= num;
}
