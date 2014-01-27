#include "ModelParse.h"
#include <string>
#include <iostream>

using namespace std;

ModelParse::ModelParse(string path)
{
  ifstream ifs;
  ifs.open(path.c_str(), ifstream::in);

  string line;
  
  while (getline(ifs, line)) {
    cout<<line<<endl;
  }

}
