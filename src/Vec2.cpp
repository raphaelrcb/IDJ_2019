#include "../include/Vec2.hpp"

Vec2::Vec2(int a, int b){
  this->x = a;
  this->y = b;
}
Vec2 Vec2::GetRotated(float angle){
    Vec2 rotated;

  rotated.x = this->x*cos(angle) + this->y*sin(angle);
  rotated.y = this->y*cos(angle) + this->x*sin(angle);


  return rotated;
}

Vec2 Vec2::operator+(const Vec2& v){
  Vec2 sum;
  sum.x = this->x + v.x;
  sum.y = this->y + v.y;

  return (v);
}
Vec2::Vec2(){

}
