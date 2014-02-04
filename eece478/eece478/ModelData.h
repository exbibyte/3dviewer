#ifndef MODELDATA_H
#define MODELDATA_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

//might be useful later on
enum eDataType
{
  NAME = 0,
  TEXTURE,
  VERTICE,
  NORMAL,
  TRIANGLE
};

//this class is used as a helper to the parser. It provides matching tags and separates data to be used by derived classes 

class ModelData{
 protected:
  vector<string> vDataItem; //contains separated data to be accessed by derived class
 public:
  string mBeginTag; //tags for parsing
  string mEndTag;  //tags for parsing
  eDataType mType;
  void SetData(string input);  //seperates space delimited input string into a vector of strings in vDataItem
  virtual void FormatData()=0; //function to save data to specific format
  virtual ~ModelData(){};
};

#endif
