#pragma once

#include "Component.hpp"
#include "Collision.h"

class Collider : public Component {

private:

  Vec2 scale;
  Vec2 offset;

public:

  Collider(GameObject& associated, Vec2 scale = Vec2(1,1), Vec2 offset = Vec2() );

  Rect box;

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);
};
