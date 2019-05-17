#pragma once

#include "Component.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include <memory>
#include <algorithm>
#include <vector>
#include <string.h>
#include <iostream>

class Component;

class GameObject{

private:
  std::vector< std::shared_ptr<Component> > components;
  bool isDead;

public:

  GameObject();
  ~GameObject();

  void Start();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(std::shared_ptr<Component> cpt);
  void RemoveComponent(std::shared_ptr<Component> cpt);

  void NotifyCollision(GameObject& other);

  bool started;
  std::shared_ptr<Component> GetComponent(std::string type);
  Rect box;
  double angleDeg;
};
