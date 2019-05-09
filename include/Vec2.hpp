#pragma once
#include <math.h>

class Vec2{

private:

public:
  float x;
  float y;
  Vec2();
  Vec2(int a  , int b);

  void Rotate(float angle);
  Vec2 GetRotated(float angle);
  float Absolute();

  Vec2 operator+(const Vec2&);
  Vec2 operator-(const Vec2&);
  Vec2 operator*(const Vec2&);
  Vec2 operator/(const Vec2&);
  Vec2 operator*(float mult);
  Vec2 operator/(float divs);

};
