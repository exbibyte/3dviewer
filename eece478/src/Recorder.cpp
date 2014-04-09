#include "Recorder.h"
#include "ModelAbstraction.h"
#include "PPM.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

#include <string>
#include <iostream>

using namespace std;

Recorder::Recorder()
{
  this->ImageCount = 0;
  this->IsRecording = false;
  this->PosX = 0;
  this->PosY = 0;
  this->Width = 1280;
  this->Height = 720;
  this->pImage = new unsigned char[this->Width*this->Height*3];
}

void Recorder::SetOutputPath(string path)
{
  this->OutputPath = path;
}

void Recorder::Start()
{ 
  if(this->IsRecording == false)
  {
    this->IsRecording = true;
  }
  cout<<"start recording.."<<endl;
}

void Recorder::End()
{
  this->IsRecording = false;
  cout<<"end recording.."<<endl;
}

void Recorder::SetImageParam(int posx, int posy, int width, int height)
{
  this->Width = width;
  this->Height = height;
  this->PosX = posx;
  this->PosY = posy;
  this->pImage = new unsigned char[width*height*3];
}

void Recorder::SaveImage()
{
  if(this->IsRecording == false)
    return;

  glReadPixels(this->PosX, this->PosY, this->Width, this->Height, GL_RGB, GL_UNSIGNED_BYTE, pImage);

  //flip image vertically
  unsigned char * forward = pImage;
  unsigned char * reverse = pImage + (this->Width * this->Height -1 )*3;

  //storage for swapping pixels
  unsigned char temp[3];

  for(int i = 0; i < this->Height/2* this->Width; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      temp[j] = *(reverse + j);    
      *(reverse + j) = *(forward + j);
      *(forward + j) = temp[j];
    }
    forward += 3;
    reverse -= 3;
  }
  
//write to file
  char imagename[16];
  char* pimagename = imagename;
  sprintf(pimagename,"%016d",this->ImageCount);
  string imagestr(pimagename);
  string filepath = this->OutputPath + imagestr+".ppm";
  cout<<"image file path: "<<filepath<<endl;
  PPM::Write(filepath, this->pImage, this->Width, this->Height);
  this->ImageCount++;
}

void Recorder::FormatAction()
{
  int count = 0;
  for(auto i: vAction)
  {
    if(count == 0)
    {
      if(i == "recorder_start")
      {
	this->Start();
      }
      else if(i == "recorder_end")
      {
	this->End();
      }
    }
  }
}
