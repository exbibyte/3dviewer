#ifndef MODEL_ENTITY_H
#define MODEL_ENTITY_H

#include <vector>
#include <tuple>

#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 


//index for accessing triangle data tuple
#define TTRIANGLEDETAIL_ID 0
#define TTRIANGLEDETAIL_VEC1ID 1
#define TTRIANGLEDETAIL_VEC2ID 2
#define TTRIANGLEDETAIL_VEC3ID 3
#define TTRIANGLEDETAIL_NORMID 4
#define TTRIANGLEDETAIL_VEC1X 5
#define TTRIANGLEDETAIL_VEC1Y 6
#define TTRIANGLEDETAIL_VEC1Z 7
#define TTRIANGLEDETAIL_VEC2X 8
#define TTRIANGLEDETAIL_VEC2Y 9
#define TTRIANGLEDETAIL_VEC2Z 10
#define TTRIANGLEDETAIL_VEC3X 11
#define TTRIANGLEDETAIL_VEC3Y 12
#define TTRIANGLEDETAIL_VEC3Z 13
#define TTRIANGLEDETAIL_NORMX 14
#define TTRIANGLEDETAIL_NORMY 15
#define TTRIANGLEDETAIL_NORMZ 16

//definition of data tuple
typedef tuple<int, int,int,int, int, float,float,float,float,float,float,float,float,float, float,float,float> tTriangleDetail;

class ModelEntity{
private:

  //sorting comparators used in linking triangles to vertices, normals, etc
  static bool fSortTriangleDetailByVec1(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByVec2(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByVec3(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByNorm(const tTriangleDetail&, const tTriangleDetail&);
  
  //vertice data
  float * pVerticeData;
  int vNumVertice;

  //VBO object
  GLuint vVbo;
  GLuint * pVbo;

public:
  ModelEntity();
  ~ModelEntity();
  
  //basic data from parsing
  ModelName * cModelName;
  ModelTexture * cModelTexture;
  ModelVertice * cModelVertice;
  ModelNormal * cModelNormal;
  ModelTriangle * cModelTriangle;
  
  //processed data for each triangle
  vector<tTriangleDetail> vtTriangleDetail;
  
  void GetUpdatedVertices(float*& data, int& num);   //helper function for creating 1D array of vertice data
  void Update();    //sort and match to create processed data
  void Draw();
  void LoadVBO();    //bind data to VBO		
};

#endif
