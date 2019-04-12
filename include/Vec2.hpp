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
  Vec2 operator+(const Vec2&);
};


// std::find_if(numbers.begin(), numbers.end(), [&](std::unique_ptr<int>& p) { return p.get() == x;});
//ué
