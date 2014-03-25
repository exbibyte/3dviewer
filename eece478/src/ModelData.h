#ifndef MODELDATA_H
#define MODELDATA_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

///type of data, might be useful later on
enum eDataType
{
  NAME = 0,
  TEXTURE,
  VERTICE,
  NORMAL,
  TRIANGLE,
  CURVE
};

///acts as a helper class to the parser. It provides matching DOM tags and separates data to be used by derived classes
class ModelData{
 protected:
  ///contains separated data to be accessed by derived class
  vector<string> vDataItem; 
 public:
  ///start tag for parsing
  string mBeginTag; 
  ///end tag for parsing
  string mEndTag;  
  //type of stored data
  eDataType mType;
  ///seperates space delimited input string into a vector of strings in vDataItem
  void SetData(string input);  
  ///function to save data to specific format
  virtual void FormatData()=0; 
  virtual ~ModelData(){};
  virtual void ClearData(){}; 
};

#endif
