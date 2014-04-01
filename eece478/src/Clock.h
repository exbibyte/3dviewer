#ifndef CLOCK_H
#define CLOCK_H

#include <string>
#include <chrono>

using namespace std;

/// provides timing and triggering ability
class Clock
{
 private:
  float Fps;

  float FpsActual;

  /// stores how many milliseconds between consecutive frames
  float AutoDuration;
  float AutoDurationScaled;

  ///current time not counting paused time in milliseconds
  float TimeSinceStart;

  chrono::high_resolution_clock::time_point TimePrev;
  chrono::high_resolution_clock::time_point Time;
  
  ///flag indicating if clock is running
  bool bRunning;

  float ClockScale;

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

  void SetClockScale(float);

  bool IsRunning();

  /// get current time in milliseconds
  float GetTime();

  /// implementation method called after each clock Tick success
  virtual void TickAction(string a){};
};

#endif
