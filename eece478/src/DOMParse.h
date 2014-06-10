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
  vector<tDOMMatcher>                  vDOMMatcher;   ///DOM types to register a match
  void                                 NestedDOM(DOMNode * node, string input);   ///helper function to get nested data
 public:
                                       DOMParse();
  DOMNode *                            GetDOM(string path);   ///factory function to generate DOM tree

};

#endif
