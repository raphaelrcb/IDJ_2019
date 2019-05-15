#pragma once

#include "Vec2.hpp"
#include "Minion.hpp"
#include <string>
#include <math.h>


#define BULLET_PATH "assets/img/minionbullet2.png"
#define BULLET_DAMAGE 500
#define BULLET_SPEED 50.0
#define BULLET_FRAMECOUNT 3
#define BULLET_FRAMETIME BULLET_FRAMECOUNT/33

class Minion;

class Bullet : public Component {

private:

  Vec2 speed;
  float distanceLeft;
  int damage;

public:

  Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();

};
