#ifndef DOMPARSE_H
#define DOMPARSE_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "DOMMatcher.h"
#include "DOMNode.h"

using namespace std;

///parses Trajectory input file and returns CurvePath entities
class DOMParse
{
 private:

  ///DOM types to register a match
  vector<tDOMMatcher> vDOMMatcher; 

  ///helper function to get nested data
  void NestedDOM(DOMNode * node, string input);

 public:
  DOMParse();

  ///factory function to generate DOM tree
  DOMNode* GetDOM(string path);

};

#endif
