#ifndef MODELDATA_H
#define MODELDATA_H

#include <string>
#include <sstream>
#include <vector>

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
};

void ModelData::SetData(string input)
/** separate data items into a vector of strings and calls formating function in a derived class*/
{
  stringstream Ss;
  Ss.str(input);
  string temp;

  //seperate each data item
  while (Ss>>temp)
  {
    this->vDataItem.push_back(temp);
    temp.clear();
  }

  this->FormatData(); //format data
}

#endif
