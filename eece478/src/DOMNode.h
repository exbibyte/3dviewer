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

  ///node type
  string Type;

  /// parent node
  DOMNode * Parent;

  /// children nodes
  vector<DOMNode *> Children;

  ///parsed data
  string Data;

  void AddChild(DOMNode * node);

  void Print();

  void PrintBreadth();

};

#endif
