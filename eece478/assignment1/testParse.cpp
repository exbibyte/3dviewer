#include "ModelParse.h"

int main(int argc, char **argv)
{
  if(argc == 1)
  { 
    cout<<"not enough argument"<<endl;
    return -1;
  }

  ModelParse testModel(argv[1]);

}
