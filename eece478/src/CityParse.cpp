#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "CityParse.h"
#include "ModelParse.h"
#include "ModelEntity.h"
#include "ModelAbstraction.h"

CityParse::CityParse()
{
}

vector<ModelAbstraction*> CityParse::ParseCity(string path)
{
  vector<ModelAbstraction*> vpEntity;

  ifstream ifs;
  stringstream Ss;

  ///open model file
  ifs.open(path.c_str(), ifstream::in);
  if(!ifs.is_open())
  {
    cout<<"error opening file: "<<path<<endl;
    return vpEntity;
  }

  string line;
  int LineNum = 0;

  ///remove #comments
  while (getline(ifs, line)) 
  {    
    size_t found = line.find("#");
    if(found != std::string::npos){
      continue;
    }

    ///skip empty line
    if(line.size()==0){
      continue;
    }

    ///record line
    Ss<<line<<" "; // save remaining lines to a single lined buffer and add space to ensure data separation
    string entitypath;
    float scale[3];
    float rotate[3];
    float translate[3];

    Ss>>entitypath;

    for(int i = 0; i < 3; i++)
    {
      Ss>>scale[i];
    }

    for(int i = 0; i < 3; i++)
    {
      Ss>>rotate[i];
    }
    for(int i = 0; i < 3; i++)
    {
      Ss>>translate[i];
    }

    //extract path to the top level city folder and add it to each building model path
    string folder = "/";
    unsigned foundfolder = path.rfind(folder);
    if(foundfolder!=std::string::npos)
    {
      entitypath = path.substr(0,foundfolder+1) + entitypath; 
    }
#ifdef DEBUG
    cout<<"model path: "<<entitypath<<endl;
    cout<<"scale: "<<scale[0]<<","<<scale[1]<<","<<scale[2]<<endl;
    cout<<"rotate: "<<rotate[0]<<","<<rotate[1]<<","<<rotate[2]<<endl;
    cout<<"translate: "<<translate[0]<<","<<translate[1]<<","<<translate[2]<<endl;
#endif
    //generate new entity
    ModelEntity * newentity;
    newentity = cModelParse.GetEntity(entitypath);
    newentity->InitializeOrientation(scale,rotate,translate);
  
    //load model information and textures and do initial update
    newentity->LoadTextureFiles();
    
    //do an initial update of triangle data
    newentity->Update();
    
    //update data in buffers to be rendered
    newentity->LoadRenderBuffer();

    vpEntity.push_back(newentity);
    newentity = NULL;
  }

  return vpEntity;
}
