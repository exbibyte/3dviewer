#include "ModelParse.h"
#include "ModelTexture.h"
#include "ModelData.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

ModelParse::ModelParse(string path)
{
  ModelTexture * cModelTexture = new ModelTexture();

  vector<ModelData*> vModelData;
  vModelData.push_back((ModelData*)cModelTexture);

  ifstream ifs;
  stringstream ss;

  ifs.open(path.c_str(), ifstream::in);

  string line;
  int LineNum = 0;

  //loop ModelData
  while (getline(ifs, line)) {
    // cout<<line<<endl;
    vModelData.at(0)->setData(line);
    // bool TagFound = false;

    // //find start tag <thing>
    // if(!TagFound)
    // {
    //   size_t found = line.find(BeginTag);
    //   if(found != std::string::npos)
    //   {
    // 	cout<<"found 'name' at position "<<found<<" line "<<LineNum<<endl;	
    // 	TagFound = true;
    //   }
    // }
    // //find end tag </thing>
    // else
    // {
    //   size_t found = line.find(EndTag);
    //   if(found != std::string::npos)
    //   {
    // 	cout<<"found 'name' at position "<<found<<" line "<<LineNum<<endl;	
    // 	TagFound = true;
    //   }
    // }
   
    //process stuff in between the tags      
    LineNum++;
  }

  delete cModelTexture;
}
