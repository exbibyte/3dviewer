#ifndef MODEL_ENTITY_H
#define MODEL_ENTITY_H

#include <vector>
#include <tuple>
#include <string>

#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

#include "PPM.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

///index for accessing triangle data tuple
#define TTRIANGLEDETAIL_ID 0
#define TTRIANGLEDETAIL_VEC1ID 1
#define TTRIANGLEDETAIL_VEC2ID 2
#define TTRIANGLEDETAIL_VEC3ID 3
#define TTRIANGLEDETAIL_NORMID 4
#define TTRIANGLEDETAIL_TEXTID 5
#define TTRIANGLEDETAIL_VEC1X 6
#define TTRIANGLEDETAIL_VEC1Y 7
#define TTRIANGLEDETAIL_VEC1Z 8
#define TTRIANGLEDETAIL_VEC2X 9
#define TTRIANGLEDETAIL_VEC2Y 10
#define TTRIANGLEDETAIL_VEC2Z 11
#define TTRIANGLEDETAIL_VEC3X 12
#define TTRIANGLEDETAIL_VEC3Y 13
#define TTRIANGLEDETAIL_VEC3Z 14
#define TTRIANGLEDETAIL_NORMX 15
#define TTRIANGLEDETAIL_NORMY 16
#define TTRIANGLEDETAIL_NORMZ 17
#define TTRIANGLEDETAIL_TEXTNAME 18
#define TTRIANGLEDETAIL_TEXT1 18
#define TTRIANGLEDETAIL_TEXT2 19
#define TTRIANGLEDETAIL_TEXT3 20
#define TTRIANGLEDETAIL_TEXT4 21
#define TTRIANGLEDETAIL_TEXT5 22
#define TTRIANGLEDETAIL_TEXT6 23

using namespace std;

///definition of data tuple
typedef tuple<int, int,int,int, int, int, float,float,float,float,float,float,float,float,float, float,float,float, string, float,float,float,float,float,float> tTriangleDetail;

///This class is a container of basic model data. It also provides functions to link basic data to generate triangle vertices and draw vertices. It can be used after OpenGL initilization functions are called. 

class ModelEntity{
private:
  ///sorting comparators used in linking triangles to vertices  
  static bool fSortTriangleDetailByVec1(const tTriangleDetail&, const tTriangleDetail&);
  ///sorting comparators used in linking triangles to vertices  
  static bool fSortTriangleDetailByVec2(const tTriangleDetail&, const tTriangleDetail&);
  ///sorting comparators used in linking triangles to vertices  
  static bool fSortTriangleDetailByVec3(const tTriangleDetail&, const tTriangleDetail&);
  ///sorting comparators used in linking triangles to normals 
  static bool fSortTriangleDetailByNorm(const tTriangleDetail&, const tTriangleDetail&);
  ///sorting comparators used in linking triangles to textures
  static bool fSortTriangleDetailByText(const tTriangleDetail&, const tTriangleDetail&);
  
  ///stores updated vertice data in an array
  float * pVerticeData;
  ///number of vertices stored in the  array
  int vNumVertice;

  ///VBO object
  GLuint vVbo;
  ///VBO object pointer
  GLuint * pVbo;

public:
  ModelEntity();
  ~ModelEntity();
  
  ///stored formatted data from parsing
  ModelName * cModelName;
  ///stored formatted data from parsing
  ModelTexture * cModelTexture;
  ///stored formatted data from parsing
  ModelVertice * cModelVertice;
  ///stored formatted data from parsing
  ModelNormal * cModelNormal;
  ///stored formatted data from parsing
  ModelTriangle * cModelTriangle;
  
  //stores processed triangle data after calling Update()
  vector<tTriangleDetail> vtTriangleDetail;
  
  ///helper function to create 1D array of vertice data from processed triangles
  void GetUpdatedVertices(float*& data, int& num);
  //sortes and matches formatted data to create processed triangles
  void Update();
  ///draws model using data linked to VBO    
  void Draw();  
  ///bind vertice array to VBO		
  void LoadVBO();    
};

#endif
