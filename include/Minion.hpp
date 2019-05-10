#pragma once

#include <memory>
#include "Component.hpp"
#include "Sprite.hpp"
#include "Game.hpp"


#define PI 3.14159265359
#define MINION_PATH "/assets/img/minion.png"
#define V_ANG_MINION 75

class Minion : public Component {

private:

  std::weak_ptr<GameObject> alienCenter;
  float arc;

public:

  Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot(Vec2 target);

};
