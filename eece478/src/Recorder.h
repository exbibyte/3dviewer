#ifndef RECORDER_H
#define RECORDER_H

#include <string>

using namespace std;

class Recorder
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
  /// sets output file
  void SetOutputPath(string path);
  /// start
  void Start();
  /// stop
  void End();
  /// write to file
  void SaveImage();
};

#endif
