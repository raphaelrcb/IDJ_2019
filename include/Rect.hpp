#pragma once

#include "Vec2.hpp"
#include <SDL2/SDL.h>

class Rect{
private:
public:
  float x;
  float y;
  float w;
  float h;
  float Contains(float mouseX, float mouseY);
};
