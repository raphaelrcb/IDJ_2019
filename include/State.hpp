#pragma once

#include <ctime>
#include <cstdlib>

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "Face.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "Music.hpp"
#include "InputManager.hpp"

class State{

private:
  // Sprite bg;
  Music music;

  bool quitRequested;
  // void Input();
  void AddObject(int mouseX, int mouseY);
  std::vector< std::shared_ptr<GameObject> > objectArray;

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};
