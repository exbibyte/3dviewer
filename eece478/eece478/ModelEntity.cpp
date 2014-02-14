#include <tuple>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#include "ModelEntity.h"
#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

using namespace std;

//comparator functions for item IDs (vertices,normals,texture,etc) in our tuple
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

bool ModelEntity::fSortTriangleDetailByText(const tTriangleDetail& A, const tTriangleDetail& B)
{
  return std::get<TTRIANGLEDETAIL_TEXTID>(A) < std::get<TTRIANGLEDETAIL_TEXTID>(B);
}


void ModelEntity::GetUpdatedVertices(float*& data, int& num)
/**
@param data 1D array of updated vertices for all triangles
@param num array size
*/
{ 
  //number of coordinates from all vertices
  num = this->vtTriangleDetail.size()*9;

#ifdef DEBUG
  cout<<"vertex coord count: "<<num<<endl; 
#endif

  //removes old data
  if(data != NULL)
  {
    delete data;
  }
  
  //assign processed triangle data to the array
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
*/
{ 
  this->vtTriangleDetail.clear();
  
  //copy IDs of basic data and texture coordinates
  for(auto i : cModelTriangle->vTriangle)
  {
    tTriangleDetail detail;
    std::get<TTRIANGLEDETAIL_ID>(detail) = std::get<TTRIANGLE_ID>(i);
    std::get<TTRIANGLEDETAIL_VEC1ID>(detail) = std::get<TTRIANGLE_VEC1ID>(i);
    std::get<TTRIANGLEDETAIL_VEC2ID>(detail) = std::get<TTRIANGLE_VEC2ID>(i);
    std::get<TTRIANGLEDETAIL_VEC3ID>(detail) = std::get<TTRIANGLE_VEC3ID>(i);
    std::get<TTRIANGLEDETAIL_NORMID>(detail) = std::get<TTRIANGLE_NORMID>(i);
    std::get<TTRIANGLEDETAIL_TEXTID>(detail) = std::get<TTRIANGLE_TEXTID>(i);
    
    std::get<TTRIANGLEDETAIL_TEXT1>(detail) = std::get<TTRIANGLE_TEXT1>(i);
    std::get<TTRIANGLEDETAIL_TEXT2>(detail) = std::get<TTRIANGLE_TEXT2>(i);
    std::get<TTRIANGLEDETAIL_TEXT3>(detail) = std::get<TTRIANGLE_TEXT3>(i);
    std::get<TTRIANGLEDETAIL_TEXT4>(detail) = std::get<TTRIANGLE_TEXT4>(i);
    std::get<TTRIANGLEDETAIL_TEXT5>(detail) = std::get<TTRIANGLE_TEXT5>(i);
    std::get<TTRIANGLEDETAIL_TEXT6>(detail) = std::get<TTRIANGLE_TEXT6>(i);
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
  
  //saves to an updated array of vertices
  int numData;
  this->GetUpdatedVertices(this->pVerticeData, numData);
  this->vNumVertice = numData/3;

  //sort triangles by normal
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByNorm); 
  //assign values when IDs match
  vector<tNormal>::iterator itNormal = this->cModelNormal->vNormal.begin(); 
  itDetail = this->vtTriangleDetail.begin(); 
  while(itNormal != this->cModelNormal->vNormal.end() && itDetail != this->vtTriangleDetail.end())   
  {
    if(std::get<TNORMAL_ID>(*itNormal) == std::get<TTRIANGLEDETAIL_NORMID>(*itDetail))
    {
      std::get<TTRIANGLEDETAIL_NORMX>(*itDetail) = std::get<TNORMAL_X>(*itNormal);
      std::get<TTRIANGLEDETAIL_NORMY>(*itDetail) = std::get<TNORMAL_Y>(*itNormal);
      std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail) = std::get<TNORMAL_Z>(*itNormal);
      itDetail++;
    }
    else
    {
      itNormal++;
    }
  }

  //sort triangles by texture
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByText); 
  //assign values when IDs match
  vector<tTexture>::iterator itTexture = this->cModelTexture->vTexture.begin(); 
  itDetail = this->vtTriangleDetail.begin(); 
  while(itTexture != this->cModelTexture->vTexture.end() && itDetail != this->vtTriangleDetail.end())   
  {
    if(std::get<TTEXTURE_ID>(*itTexture) == std::get<TTRIANGLEDETAIL_TEXTID>(*itDetail))
    {
      std::get<TTRIANGLEDETAIL_TEXTNAME>(*itDetail) = std::get<TTEXTURE_NAME>(*itTexture);
      cout<<std::get<TTRIANGLEDETAIL_TEXTNAME>(*itDetail)<<endl;
      itDetail++;
    }
    else
    {
      itTexture++;
    }
  }

}

void ModelEntity::LoadVBO()
/**
link updated vertice array to the VBO
*/
{
  glBindBuffer(GL_ARRAY_BUFFER, this->vVbo);
  glBufferData(GL_ARRAY_BUFFER, this->vNumVertice*3*sizeof(GLfloat), this->pVerticeData, GL_STATIC_DRAW);
}

void ModelEntity::Draw()
/**
Draw what's linked to the VBO
*/
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vVbo);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, this->vNumVertice);
}

ModelEntity::ModelEntity()
/**
Creates a vertex buffer object. Initializes vertex data pointer
*/
{
    this->pVerticeData = NULL;
    this->pVbo = &this->vVbo;
    glGenBuffers(1, this->pVbo);
}

ModelEntity::~ModelEntity()
/**
Deallocates memory
*/
{
  delete this->pVerticeData;
  this->pVerticeData = NULL;
}
