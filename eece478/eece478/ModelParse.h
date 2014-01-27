#ifndef MODELPARSE_H
#define MODELPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

typedef struct{
  string name;
}zTexture;

typedef struct{
  double Vertice[3];
}zVertice;

typedef struct{
  double Normal[3];
}zNormal;

typedef struct{
  int Indices[3];
  int NormalIndex;
  int TextureIndex;
  double TextureCoord[6];
}zTriangle;

using namespace std;

class ModelParse
{
protected:
  vector<zTexture> vecTexture;
  vector<zVertice> vecVertice;
  vector<zNormal> vecNormal;
  vector<zTriangle> vecTriangle;
public:
  //load model and store model info within the class
  ModelParse(string path);
};

#endif
