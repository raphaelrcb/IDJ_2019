#pragma once

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Music.hpp"

class State{

private:
  Sprite bg;
  Music music;
  bool quitRequested;
  void Input();
  void AddObject(int mouseX, int mouseY);
  std::vector<std::unique_ptr<GameObject>> objectArray;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};
