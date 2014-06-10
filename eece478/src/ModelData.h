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
  vector<string>           vDataItem;   ///contains separated data to be accessed by derived class
 public:
  string                   mBeginTag;   ///start tag for parsing
  string                   mEndTag;    ///end tag for parsing
  eDataType                mType;  //type of stored data
  void                     SetData(string input);  ///seperates space delimited input string into a vector of strings in vDataItem
  virtual void             FormatData()=0;  ///function to save data to specific format
  virtual                  ~ModelData(){};
  virtual void             ClearData(){}; 
};

#endif
