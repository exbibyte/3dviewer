#ifndef DOMNODE_H
#define DOMNODE_H

#include <string>
#include <vector>

using namespace std;

class DOMNode
{
 public:
                         DOMNode();
                         ~DOMNode();
  string                 Type;
  DOMNode *              Parent;
  vector<DOMNode *>      Children;  
  string                 Data;   ///parsed data
  void                   AddChild(DOMNode * node);
  void                   Print();
  void                   PrintBreadth();

};

#endif
