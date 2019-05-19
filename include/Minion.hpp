#pragma once

#include <memory>
#include "Component.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"

class Bullet;

#define PI 3.14159265359
#define MINION_PATH "assets/img/minion.png"
#define MINION_BULLET_PATH "assets/img/minionbullet2.png"
#define V_ANG_MINION 0.75
#define MINION_RADIUS 180
#define MINION_BULLET_FRAMECOUNT 3
#define MINION_BULLET_FRAMETIME 1
#define MINION_BULLET_RANGE 1000

#define MINION_DEATH_SPRITES "assets/img/miniondeath.png"
#define MINION_DEATH_SOUND "assets/audio/boom.wav"
#define MINION_DEATH_FRAMECOUNT 4
#define MINION_DEATH_FRAMETIME 0.1

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
  void NotifyCollision(GameObject& other);


};
