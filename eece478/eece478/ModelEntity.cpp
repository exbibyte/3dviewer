#include <tuple>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "ModelEntity.h"
#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"


bool ModelEntity::fSortTriangleDetailByVec1(const tTriangleDetail& A, const tTriangleDetail& B)
{
  return std::get<TTRIANGLEDETAIL_VEC1ID>(A) < std::get<TTRIANGLEDETAIL_VEC1ID>(B);
}

bool ModelEntity::fSortTriangleDetailByVec2(const tTriangleDetail& A, const tTriangleDetail& B)
{
  return std::get<TTRIANGLEDETAIL_VEC2ID>(A) < std::get<TTRIANGLEDETAIL_VEC2ID>(B);
}

bool ModelEntity::fSortTriangleDetailByVec3(const tTriangleDetail& A, const tTriangleDetail& B)
{
  return std::get<TTRIANGLEDETAIL_VEC3ID>(A) < std::get<TTRIANGLEDETAIL_VEC3ID>(B);
}

bool ModelEntity::fSortTriangleDetailByNorm(const tTriangleDetail& A, const tTriangleDetail& B)
{
  return std::get<TTRIANGLEDETAIL_NORMID>(A) < std::get<TTRIANGLEDETAIL_NORMID>(B);
}

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
  cout<<"vertex data count"<<num<<endl; 
#endif

  data = new float[num];

  for(auto i : this->cModelVertice->vVertice)
  {
    *data = std::get<TVERTICE_X>(i);
    data++;
    *data = std::get<TVERTICE_Y>(i);
    data++;
    *data = std::get<TVERTICE_Z>(i);
    data++;
  }
  data -= num;
}

void ModelEntity::GetUpdatedVertices(float*& data, int& num)
/**
return:
data: 1D array of updated vertice data matched for each triangle
num: array size
*/
{
  this->vNumVertice = (this->vtTriangleDetail.size()*3);
  num = this->vNumVertice*3;

#ifdef DEBUG
  cout<<"vertex data count"<<num<<endl; 
#endif

  data = new float[num];

  for(auto i : this->vtTriangleDetail)
  {
    *data = std::get<TTRIANGLEDETAIL_VEC1X>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC1Y>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC1Z>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC2X>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC2Y>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC2Z>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC3X>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC3Y>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_VEC3Z>(i);
    data++;
  }
  data -= num;
}

void ModelEntity::Update()
/**
Links triangles to vertices, normals, and textures to generate updated triangle data
Currently vertices are updated
*/
{ 
  this->vtTriangleDetail.clear();
  
  //copy IDs
  for(auto i : cModelTriangle->vTriangle)
  {
    tTriangleDetail detail;
    std::get<TTRIANGLEDETAIL_ID>(detail) = std::get<TTRIANGLE_ID>(i);
    std::get<TTRIANGLEDETAIL_VEC1ID>(detail) = std::get<TTRIANGLE_VEC1ID>(i);
    std::get<TTRIANGLEDETAIL_VEC2ID>(detail) = std::get<TTRIANGLE_VEC2ID>(i);
    std::get<TTRIANGLEDETAIL_VEC3ID>(detail) = std::get<TTRIANGLE_VEC3ID>(i);
    std::get<TTRIANGLEDETAIL_NORMID>(detail) = std::get<TTRIANGLE_NORMID>(i);
    this->vtTriangleDetail.push_back(detail);
  }

  //sort triangles by 1st vertex
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByVec1); 
  //assign values when IDs match
  vector<tVertice>::iterator itVertice = this->cModelVertice->vVertice.begin(); 
  vector<tTriangleDetail>::iterator itDetail = this->vtTriangleDetail.begin(); 
  while(itVertice != this->cModelVertice->vVertice.end() && itDetail != this->vtTriangleDetail.end())   
  {
    if(std::get<TVERTICE_ID>(*itVertice) == std::get<TTRIANGLEDETAIL_VEC1ID>(*itDetail))
    {
      std::get<TTRIANGLEDETAIL_VEC1X>(*itDetail) = std::get<TVERTICE_X>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC1Y>(*itDetail) = std::get<TVERTICE_Y>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC1Z>(*itDetail) = std::get<TVERTICE_Z>(*itVertice);
      itDetail++;
    }
    else
    {
      itVertice++;
    }
  }

  //sort triangles by 2nd vertex
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByVec2); 
  //assign values when IDs match
  itVertice = this->cModelVertice->vVertice.begin(); 
  itDetail = this->vtTriangleDetail.begin(); 
  while(itVertice != this->cModelVertice->vVertice.end() && itDetail != this->vtTriangleDetail.end())   
  {
    if(std::get<TVERTICE_ID>(*itVertice) == std::get<TTRIANGLEDETAIL_VEC2ID>(*itDetail))
    {
      std::get<TTRIANGLEDETAIL_VEC2X>(*itDetail) = std::get<TVERTICE_X>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC2Y>(*itDetail) = std::get<TVERTICE_Y>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC2Z>(*itDetail) = std::get<TVERTICE_Z>(*itVertice);
      itDetail++;
    }
    else
    {
      itVertice++;
    }
  }

  //sort triangles by 3rd vertex
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByVec3); 
  //assign values when IDs match
  itVertice = this->cModelVertice->vVertice.begin(); 
  itDetail = this->vtTriangleDetail.begin(); 
  while(itVertice != this->cModelVertice->vVertice.end() && itDetail != this->vtTriangleDetail.end())   
  {
    if(std::get<TVERTICE_ID>(*itVertice) == std::get<TTRIANGLEDETAIL_VEC3ID>(*itDetail))
    {
      std::get<TTRIANGLEDETAIL_VEC3X>(*itDetail) = std::get<TVERTICE_X>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC3Y>(*itDetail) = std::get<TVERTICE_Y>(*itVertice);
      std::get<TTRIANGLEDETAIL_VEC3Z>(*itDetail) = std::get<TVERTICE_Z>(*itVertice);
      itDetail++;
    }
    else
    {
      itVertice++;
    }
  }
}
