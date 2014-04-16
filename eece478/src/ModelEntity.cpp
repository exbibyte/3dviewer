#include <tuple>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#include "ModelName.h"
#include "ModelEntity.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"
#include "ModelAbstraction.h"

#include "PPM.hpp"

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

void ModelEntity::GetUpdatedNormals(float*& data, int& num)
/**
@param data 1D array of updated normals for all triangles
@param num array size
*/
{ 
  //number of coordinates from all vertices
  num = this->vtTriangleDetail.size()*3;

#ifdef DEBUG
  cout<<"normal coord count: "<<num<<endl; 
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
    *data = std::get<TTRIANGLEDETAIL_NORMX>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_NORMY>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_NORMZ>(i);
    data++;
  }
  data -= num;
}

void ModelEntity::GetUpdatedTextureCoords(float*& data, int& num)
/**
@param data 1D array of updated texture coordinates for all triangles
@param num array size
*/
{ 
  //number of coordinates from all vertices
  num = this->vtTriangleDetail.size()*6;

#ifdef DEBUG
  cout<<"texture coord count: "<<num<<endl; 
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
    *data = std::get<TTRIANGLEDETAIL_TEXT1>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_TEXT2>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_TEXT3>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_TEXT4>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_TEXT5>(i);
    data++;
    *data = std::get<TTRIANGLEDETAIL_TEXT6>(i);
    data++;
  }
  data -= num;
}

void ModelEntity::UpdateInterleavedArray()
/**
updates interleaved render data buffers according to texture
*/
{ 
  //sort triangle by texture id
  std::sort(this->vtTriangleDetail.begin(), this->vtTriangleDetail.end(), fSortTriangleDetailByText); 
  vector<tTriangleDetail>::iterator itDetail1 = this->vtTriangleDetail.begin(); 
  vector<tTriangleDetail>::iterator itDetail2 = this->vtTriangleDetail.begin(); 

  int bufnum;
  
  //copy data into rendering buffers for each specfic texture
  while(itDetail2 != this->vtTriangleDetail.end())      
  {
    //find where texture changes and start copying
    if(std::get<TTRIANGLEDETAIL_TEXTID>(*itDetail1) != std::get<TTRIANGLEDETAIL_TEXTID>(*itDetail2))
    {
      int datanum = (itDetail2 - itDetail1)*24;
      float * data = new float[datanum];

      //copy data into buffer
      while(itDetail1 != itDetail2)
      {      
	*data = std::get<TTRIANGLEDETAIL_VEC1X>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC1Y>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC1Z>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT1>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT2>(*itDetail1);
	data++;

	*data = std::get<TTRIANGLEDETAIL_VEC2X>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC2Y>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC2Z>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT3>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT4>(*itDetail1);
	data++;

	*data = std::get<TTRIANGLEDETAIL_VEC3X>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC3Y>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_VEC3Z>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT5>(*itDetail1);
	data++;
	*data = std::get<TTRIANGLEDETAIL_TEXT6>(*itDetail1);
	data++;

	itDetail1++;
      }
      
      //get texture id of the current data
      bufnum = std::get<TTRIANGLEDETAIL_TEXTID>(*(itDetail1-1));
      
      //save number of data
      this->pNumRenderData[bufnum] = datanum;
      data -= datanum;
      
      //deallocate previous data
      if(this->pRenderData[bufnum]!=NULL)
      {
	delete [] this->pRenderData[bufnum];
      }

      //save the texture id 
      this->vTexturePassId.push_back(bufnum);

      //save render data
      this->pRenderData[bufnum] = data;

      data = NULL;
    }
    else
    {
      itDetail2++;
    }
  }

  //copy the last portion
  int datanum = (this->vtTriangleDetail.end() - itDetail1)*24;
  float * data;
  
  if(datanum > 0)
  {
    data = new float[datanum];
    while(itDetail1 != this->vtTriangleDetail.end())
    {      
      *data = std::get<TTRIANGLEDETAIL_VEC1X>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC1Y>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC1Z>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT1>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT2>(*itDetail1);
      data++;

      *data = std::get<TTRIANGLEDETAIL_VEC2X>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC2Y>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC2Z>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT3>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT4>(*itDetail1);
      data++;

      *data = std::get<TTRIANGLEDETAIL_VEC3X>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC3Y>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_VEC3Z>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMX>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMY>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_NORMZ>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT5>(*itDetail1);
      data++;
      *data = std::get<TTRIANGLEDETAIL_TEXT6>(*itDetail1);
      data++;

      itDetail1++;
    }

    //get texture id of the current data
    bufnum = std::get<TTRIANGLEDETAIL_TEXTID>(*(itDetail1-1));
      
    //save number of data
    this->pNumRenderData[bufnum] = datanum;
    data -= datanum;
  
    //dellocate previous data
    if(this->pRenderData[bufnum]!= NULL)
    {
      delete [] this->pRenderData[bufnum];
    }

    //save the texture id
    this->vTexturePassId.push_back(bufnum);

    //save render data
    this->pRenderData[bufnum] = data;
    data = NULL;
  }
}

void ModelEntity::Initialize(ModelName *a, ModelTexture *b, ModelVertice *c, ModelNormal *d, ModelTriangle *e)
{
  this->cModelName = a;
  this->cModelTexture = b;
  this->cModelVertice = c;
  this->cModelNormal = d;
  this->cModelTriangle = e;

  //set ModelAbstraction name
  if(this->cModelName->vName.empty() == false)
  {
    tName tname = this->cModelName->vName.at(0);
    this->Name = std::get<1>(tname); // some problem with getting DEFINES in ModelName.h
#ifdef DEBUG
    cout<<"model name: "<<this->Name<<endl;
#endif
  }
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

      itDetail++;
    }
    else
    {
      itTexture++;
    }
  }

  //update rendering buffer
  this->UpdateInterleavedArray();
}

void ModelEntity::LoadRenderBuffer()
/**
link updated render data to buffers
*/
{
  for(auto i : this->vTexturePassId)
  {
    glBindBuffer(GL_ARRAY_BUFFER, this->pRbo[i]);
    glBufferData(GL_ARRAY_BUFFER, this->pNumRenderData[i]*sizeof(GLfloat), this->pRenderData[i], GL_STATIC_DRAW);
  }
}

void ModelEntity::Draw()
/**
Draw what's linked to the VBO, NBO, TBO
*/
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  //texture switching
  for(auto i : vTexturePassId)
  {
    glBindTexture(GL_TEXTURE_2D, pTextureID[i]);       
    glBindBuffer(GL_ARRAY_BUFFER, this->pRbo[i]);
    glVertexPointer(3, GL_FLOAT, 8*sizeof(GLfloat), 0);
    glNormalPointer(GL_FLOAT, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));        
    glTexCoordPointer(2, GL_FLOAT, 8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));  
    glDrawArrays(GL_TRIANGLES, 0, this->pNumRenderData[i]*3);
  } 
  
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

ModelEntity::ModelEntity()
/**
Creates a vertex buffer object. Initializes vertex data pointer
*/
{
    this->pRbo = NULL;
    this->pTextureID = NULL;
    this->pRenderData = NULL;
    this->pNumRenderData = NULL;
    this->vNumTextureImg = 0;
}

void ModelEntity::CleanUp()
/**
Delete pointer data
*/
{
  glDeleteBuffers(this->vNumTextureImg, this->pRbo);

  for(int i = 0; i < this->vNumTextureImg; i++)
  {
    if(this->pRenderData[i] != NULL)
    {
      delete [] this->pRenderData[i];
      this->pRenderData[i] = NULL;
    }
  }

  this->vNumTextureImg = 0;

  if(this->pRenderData != NULL)
  {
    delete [] pRenderData;
    pRenderData = NULL;
  }

  if(this->pTextureID != NULL)
  {
    glDeleteTextures(this->vNumTextureImg,this->pTextureID);
    delete [] this->pTextureID;
    this->pTextureID = NULL;
  }

  if(this->pRbo != NULL)
  {  
    delete [] this->pRbo;
    this->pRbo = NULL;
  }

  if(this->pNumRenderData != NULL)
  {
    delete [] this->pNumRenderData;
    this->pNumRenderData = NULL;
  }

  this->vTexturePassId.clear();
}

ModelEntity::~ModelEntity()
/**
Deallocates memory
*/
{
  this->CleanUp();
}

void ModelEntity::LoadTextureFiles()
/**
Load texture image files and bind to OpenGL
*/
{ 
  //delete previous data
  this->CleanUp();

  //get number of files to load
  this->vNumTextureImg = this->cModelTexture->vTexture.size();
  this->pTextureID = new GLuint[this->vNumTextureImg];

  //initialize render buffers
  this->pRbo = new GLuint[this->vNumTextureImg];
  glGenBuffers(this->vNumTextureImg, this->pRbo);

  //initilize arrays for rendering interleaved vertices, normals, texture coordinates for specific textures
  this->pNumRenderData = new int[this->vNumTextureImg];
  this->pRenderData = new float*[this->vNumTextureImg];

  for(int i = 0; i < this->vNumTextureImg; i++)
  {
    this->pRenderData[i] = NULL;
  }

  //generate texture holders
  glGenTextures(this->vNumTextureImg,this->pTextureID);

  //texture counter
  int j = 0;

  //load each texture into opengl
  for(auto i : this->cModelTexture->vTexture)
  {
    //get texture from file
    string FileName = this->ModelFilePath + std::get<TTEXTURE_NAME>(i);
    int width;
    int height;
    GLubyte * ImgData = PPM::Read(FileName, width, height);

    //bind texture to current texture holder
    glBindTexture(GL_TEXTURE_2D, this->pTextureID[j]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //pass texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ImgData);

    //let opengl automatically build mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //delte image data
    delete [] ImgData;
    ImgData = NULL;

    j++;
  }
}
