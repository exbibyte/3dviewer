#include <iostream>

#include "DOMParse.h"
#include "DOMNode.h"

using namespace std;

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    cout<<"need DOM file"<<endl;
  }

  DOMParse parser;

  DOMNode* root = parser.GetDOM(argv[1]);

  root->PrintBreadth();
  
}
