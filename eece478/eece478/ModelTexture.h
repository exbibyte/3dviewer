#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include "ModelData.h"

#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

class ModelTexture: ModelData
{
 public:
  ModelTexture();
  tuple<double,double,double> tVertice;
  vector<tuple<double,double,double>> vVertice;
  void setData(string input);
};

ModelTexture::ModelTexture()
{
  this->mType = TEXTURE;
}

void ModelTexture::setData(string input)
{
  cout<<"texture: "<<input<<endl;
  /* stringstream ss; */
  /* double temp; */
  /* double data[3]; */
  /* ss.str(input); */
  /* int i = 0; */
  /* while (ss>>temp) */
  /* { */
  /*   tuple<double,double,double> NewVertice; */
  /*   data[i] = temp; */
  /*   i++; */
  /*   if(i>=2) */
  /*   { */
  /*     i=0; */
  /*     NewVertice = std::make_tuple (data[0],data[1],data[2]); */
  /*     this->vVertice.push_back(NewVertice); */
  /*   } */
  /* } */
}

#endif
