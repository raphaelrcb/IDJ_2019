#pragma once

#include "Vec2.hpp"
#include "Minion.hpp"
#include <string>
#include <math.h>


#define BULLET_DAMAGE 500
#define BULLET_SPEED 50.0


class Minion;

class Bullet : public Component {

private:

  Vec2 speed;
  float distanceLeft;
  int damage;

public:

  Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount = 1, float frameTime = 1);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();

};
