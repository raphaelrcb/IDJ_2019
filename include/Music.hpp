#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Music{

private:
  Mix_Music* music;

public:
  Music();
  Music(std::string file);
  ~Music();
  void Play(int times = -1);
  void Stop(int msToStop = 1500);
  void Open(std::string file);
  bool IsOpen();
};