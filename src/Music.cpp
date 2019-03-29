#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../include/Music.hpp"

Music::Music(){
  music = nullptr;
}

Music::Music(std::string file){
  music = nullptr;
  Open(file);
}

void Music::Play(int times){
  if (music != nullptr){
    if (Mix_PlayMusic(music, times) == -1) {
      std::cout << "Can't play music file: " << SDL_GetError()  << std::endl;
    }
  }
  else {
    std::cout << "no music loaded" << std::endl;
  }
}

void Music::Stop(int msToStop){
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
  const char* MusicFile = file.c_str();
  music = Mix_LoadMUS(MusicFile);
  if (music == nullptr){
    std::cout << "Can't open, music file null: " << SDL_GetError()  << std::endl;
  }
}

bool Music::IsOpen(){
  if (music == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

Music::~Music(){
 Stop(0);
 Mix_FreeMusic(music);
}
