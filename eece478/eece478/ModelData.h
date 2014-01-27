#ifndef MODELDATA_H
#define MODELDATA_H

#include <string>

enum eDataType
{
  NAME = 0,
  TEXTURE,
  VERTICE,
  NORMAL,
  TRIANGLE
};

class ModelData{
 public:
  string mBeginTag;
  string mEndTag;
  eDataType mType;
  virtual void setData(string input)=0;
};

#endif
