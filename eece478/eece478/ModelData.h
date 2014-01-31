#ifndef MODELDATA_H
#define MODELDATA_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum eDataType
{
  NAME = 0,
  TEXTURE,
  VERTICE,
  NORMAL,
  TRIANGLE
};

class ModelData{
 protected:
  vector<string> vDataItem;
 public:
  string mBeginTag;
  string mEndTag;
  eDataType mType;
  void SetData(string input);
  virtual void FormatData()=0;
  virtual ~ModelData(){};
};

#endif
