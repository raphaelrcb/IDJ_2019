#pragma once

#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Music.hpp"

class State{

private:
  Sprite bg;
  Music music;
  bool quitRequested;

public:
  State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};
