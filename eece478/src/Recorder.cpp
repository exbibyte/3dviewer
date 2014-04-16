#include "Recorder.h"
#include "ModelAbstraction.h"
#include "PPM.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h> 

#include <string>
#include <iostream>
#include <stdlib.h>

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

void Recorder::SetImageParamSize(int width, int height)
{
  this->Width = width;
  this->Height = height;
  this->pImage = new unsigned char[width*height*3];
}

void Recorder::SetImageParamPosition(int posx, int posy)
{
  this->PosX = posx;
  this->PosY = posy;
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

  if(this->vAction.empty())
    return;

  //get action type
  string actiontype = this->vAction[0];

  if(actiontype == "recorder_start")
  {
    this->Start();
  }
  else if(actiontype == "recorder_end")
  {
    this->End();
  }
  else if(actiontype == "recorder_imagesize")
  {

    if(this->vAction.size() < 3)
      return;

    int w = atof(this->vAction[1].c_str());
    int h = atof(this->vAction[2].c_str());
    if(w == 0.0 || h == 0.0)
      return;

    //resize output image
    this->SetImageParamSize(w, h);
  }
  else if(actiontype == "recorder_imageposition")
  {
    if(this->vAction.size() < 3)
      return;

    int x = atof(this->vAction[1].c_str());
    int y = atof(this->vAction[2].c_str());
    if(x == 0.0 || y == 0.0)
      return;

    //reposition output image
    this->SetImageParamPosition(x, y);
  }
}
