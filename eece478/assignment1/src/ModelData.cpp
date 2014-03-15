#include <sstream>
#include <string>
#include <vector>
#include "ModelData.h"

void ModelData::SetData(string input)
/** separate data items into a vector of strings and calls formating function in a derived class
@param input single lined string data to be separated
*/
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
