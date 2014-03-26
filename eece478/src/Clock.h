#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
 private:
  float Fps;

  ///time in seconds
  float TimeSinceStart;

  int TimePrev;
  int Time;
  
  ///flag indicating if clock is running
  bool bRunning;

 public:

  Clock();

  /// sets frames per second
  bool SetFps(float fps);

  /// runs clock if fps is valid and clock is not paused
  bool Tick();

  /// runs the clock
  void Run();

  /// pauses the clock
  void Pause();

  float GetFps();

  bool IsRunning();

  float GetTime();
};

#endif
