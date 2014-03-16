#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>  

#include "CityParse.h"
#include "ModelAbstraction.h"

#define GLUT_DISABLE_ATEXIT_HACK

int main(int argc, char** argv)
{
  if(argc < 2)
    cout<<"input not valid"<<endl;

 //boilerplate
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize (500, 500); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Assignment 1");
  
  //initialize glew for vertex shader
  GLenum err = glewInit();
  if(GLEW_OK != err)
  {
    cout<<"glew init failed"<<endl;
    return -1;
  }

  CityParse cCityParse;
  
  vector<ModelAbstraction*> vpEntity;

  vpEntity = cCityParse.ParseCity(argv[1]); 

  for(auto& i : vpEntity)
  {
    delete i;
    i = NULL;
  }

  return 0;
}
