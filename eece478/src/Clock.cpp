#include "Clock.h"

#include <time.h>
#include <sstream>
#include <string>

using namespace std;

Clock::Clock()
{
  this->Fps = -1;
  this->bRunning = false;
  this->TimeSinceStart = 0;
}

bool Clock::SetFps(float fps)
{
  if(fps <= 0)
    return false;

  this->Fps = fps;
  this->AutoDuration = (float)1.0/fps;

  return true;
}

bool Clock::Tick()
{
  if(this->Fps <= 0)
    return false;
  
  if(this->bRunning == false)
    return false;

  float duration;
  
  //get duration between previous tick and now
  this->Time = clock();
  duration = (float)(this->Time - this->TimePrev)/CLOCKS_PER_SEC;
  
  //test if this tick is complete or need more time
  if(duration < this->AutoDuration)
    return false;

  //adjust fps automatically
  this->FpsActual = 1/duration;

  if(FpsActual < this->Fps * 0.9)
  {
    this->AutoDuration--;
  }
  else if(FpsActual > this->Fps * 1.1)
  {
    this->AutoDuration++;  
  }

  //save runnning time 
  this->TimeSinceStart += this->Time - this->TimePrev;

  //tick complete
  this->TimePrev = this->Time; 
  
  //fire message of tick completion
  stringstream ss;
  ss << this->TimeSinceStart;

  this->TickAction(ss.str()); 

  return true;
}

void Clock::Run()
{
  this->bRunning = true;

  this->TimePrev = clock();
}

void Clock::Pause()
{
  this->bRunning = false;
}

float Clock::GetFps()
{
  return this->Fps;
}

bool Clock::IsRunning()
{
  return this->bRunning;
}

float Clock::GetTime()
{
  return this->TimeSinceStart/CLOCKS_PER_SEC;
}

