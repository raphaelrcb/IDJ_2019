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

  Rect();
  Rect(float a, float b, float c, float d);
  bool Contains(float mouseX, float mouseY);
  Vec2 Get();
  Vec2 GetCenter();

  void operator=(const Vec2& v);
  void operator+=(const Vec2& v);

};
