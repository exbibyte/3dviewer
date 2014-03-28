#ifndef CLOCK_H
#define CLOCK_H

#include <string>

using namespace std;

/// provides timing and triggering ability
class Clock
{
 private:
  float Fps;

  float FpsActual;
  /// used for fps adjustment
  float AutoDuration;

  ///current time not counting paused time
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

  /// get current time in seconds
  float GetTime();

  /// implementation method called after each clock Tick success
  virtual void TickAction(string a){};
};

#endif
