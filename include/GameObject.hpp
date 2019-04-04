#pragma once

#include "Component.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include <memory>
#include <vector>
#include <string.h>
#include <iostream>

class Component;

class GameObject{
private:
  std::vector< std::unique_ptr<Component>* > components;
  bool isDead;
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(std::unique_ptr<Component>* cpt);
  std::unique_ptr<Component>* GetComponent(std::string type);
  Rect box;
};
