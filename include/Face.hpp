#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Sound.hpp"
#include <memory>


class Face : public Component{
private:
  int hitpoints;
public:
  Face(GameObject& associated);
  void Damage(int damage);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
