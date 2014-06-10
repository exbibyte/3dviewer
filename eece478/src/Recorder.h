#ifndef RECORDER_H
#define RECORDER_H

#include <string>

#include "ModelAbstraction.h"

using namespace std;

class Recorder : public ModelAbstraction
{
 private:
  bool                    IsRecording;
  int                     PosX;
  int                     PosY;
  int                     Width;
  int                     Height;
  string                  OutputPath;
  unsigned char *         pImage;
  int                     ImageCount;
 public:
                          Recorder();
  void                    SetImageParam(int posx, int posy, int width, int height); 
  void                    SetImageParamSize(int w, int h);
  void                    SetImageParamPosition(int x, int y);
  void                    SetOutputPath(string path);
  void                    Start();
  void                    End();
  void                    SaveImage();
  void                    FormatAction();  ///implemented method from ModelAbstraction for recording
};

#endif
