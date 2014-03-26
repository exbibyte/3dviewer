#include "Clock.h"
#include <time.h>

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

  return true;
}

bool Clock::Tick()
{
  if(this->Fps <= 0)
    return false;
  
  if(this->bRunning == false)
    return false;

  float duration;
  
  do
  {
    this->Time = clock();
    duration = (float)(this->Time - this->TimePrev)/CLOCKS_PER_SEC;
  }while(duration < 1.0/(this->Fps));

  this->TimeSinceStart += this->Time - this->TimePrev;

  this->TimePrev = this->Time;  

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

