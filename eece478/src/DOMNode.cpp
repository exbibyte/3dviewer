#include "DOMNode.h"

#include <iostream>

using namespace std;

DOMNode::DOMNode()
{
  this->Parent = NULL;
  this->Type.clear();
  this->Data.clear();
}

DOMNode::~DOMNode()
{
  for(auto i : this->Children)
  {
    if(i != NULL)
    {
      delete i;
    }
    i = NULL;
  }

  this->Children.clear();
}

void DOMNode::AddChild(DOMNode * node)
{
  this->Children.push_back(node);
}

void DOMNode::Print()
{
  cout<<this->Type<<": ";
  cout<<this->Data<<endl;
}

void DOMNode::PrintBreadth()
{ 
  for(auto i : this->Children)
  {
    i->Print();
  }
  
  for(auto i : this->Children)
  {
    i->PrintBreadth();
  }
}
