#pragma once

#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include <string.h>
#include <iostream>


class GameObject;

class Component{

private:

public:
  Component(GameObject& associated);
  virtual ~Component();
  virtual void Start();

  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual bool Is(std::string type) = 0;


protected:
  GameObject& associated;

};
