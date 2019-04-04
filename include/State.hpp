#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "Face.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include <ctime>
#include <cstdlib>



class State{

private:
  // Sprite bg;
  Music music;
  bool quitRequested;
  void Input();
  void AddObject(int mouseX, int mouseY);
  std::vector< std::unique_ptr<GameObject> > objectArray;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};
