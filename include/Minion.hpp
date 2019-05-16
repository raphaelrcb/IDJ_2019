#pragma once

#include <memory>
#include "Component.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Bullet.hpp"

class Bullet;

#define PI 3.14159265359
#define MINION_PATH "assets/img/minion.png"
#define MINION_BULLET_PATH "assets/img/minionbullet2.png"
#define V_ANG_MINION 0.75
#define MINION_RADIUS 180
#define MINION_BULLET_FRAMECOUNT 3
#define MINION_BULLET_FRAMETIME MINION_BULLET_FRAMECOUNT/33

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
