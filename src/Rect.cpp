#include <iostream>
#include <SDL2/SDL.h>
#include "../include/Rect.hpp"
Rect::Rect(){
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}
Rect::Rect(float a, float b, float c, float d){
  this->x = a;
  this->y = b;
  this->w = c;
  this->h = d;
}
bool Rect::Contains(float mouseX, float mouseY){

  if (mouseX >= this->x && mouseX <= this->x+this->w && mouseY >= this->y && mouseY <= this->y+this->h){
    return true;
  } else {
    return false;
  }


}
