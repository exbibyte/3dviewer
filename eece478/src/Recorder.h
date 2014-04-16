#ifndef RECORDER_H
#define RECORDER_H

#include <string>

#include "ModelAbstraction.h"

using namespace std;

class Recorder : public ModelAbstraction
{
 private:
  bool IsRecording;
  int PosX;
  int PosY;
  int Width;
  int Height;
  string OutputPath;
  unsigned char * pImage;
  int ImageCount;
 public:
  Recorder();
  /// sets image parameter
  void SetImageParam(int posx, int posy, int width, int height); 
  /// sets image parameter
  void SetImageParamSize(int w, int h);
  /// sets image parameter
  void SetImageParamPosition(int x, int y);
  /// sets output file
  void SetOutputPath(string path);
  /// start
  void Start();
  /// stop
  void End();
  /// write to file
  void SaveImage();

  ///implemented method from ModelAbstraction for recording
  void FormatAction();
};

#endif
