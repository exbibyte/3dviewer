#ifndef MODEL_ENTITY_H
#define MODEL_ENTITY_H

#include <vector>
#include <tuple>

#include "ModelName.h"
#include "ModelTexture.h"
#include "ModelVertice.h"
#include "ModelNormal.h"
#include "ModelTriangle.h"

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

typedef tuple<int, int,int,int, int, float,float,float,float,float,float,float,float,float, float,float,float> tTriangleDetail;

class ModelEntity{
private:
  static bool fSortTriangleDetailByVec1(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByVec2(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByVec3(const tTriangleDetail&, const tTriangleDetail&);
  static bool fSortTriangleDetailByNorm(const tTriangleDetail&, const tTriangleDetail&);
  
public:
  int vNumVertice;
  ModelName * cModelName;
  ModelTexture * cModelTexture;
  ModelVertice * cModelVertice;
  ModelNormal * cModelNormal;
  ModelTriangle * cModelTriangle;
  
  vector<tTriangleDetail> vtTriangleDetail;
  
  void GetVertices(float*& data, int& num);
  void GetUpdatedVertices(float*& data, int& num);
  void Update();
};

#endif
