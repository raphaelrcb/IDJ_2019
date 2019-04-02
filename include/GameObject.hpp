#pragma once

#include <string.h>
#include <iostream>
#include "Component.hpp"
#include "Rect.hpp"

class GameObject{
private:
  std::vector<Component*> components;
  bool isDead;
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(std::string type);
  Rect box;
};
