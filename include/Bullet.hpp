#pragma once

#include "Vec2.hpp"
#include "Component.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include <string>
#include <math.h>


#define BULLET_DAMAGE 100
#define BULLET_SPEED 500.0


class Minion;

class Bullet : public Component {

private:

  Vec2 speed;
  float distanceLeft;
  int damage;

public:

  Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount = 1, float frameTime = 1, bool targetsPlayer = true);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();
  void NotifyCollision(GameObject& other);

  bool targetsPlayer;

};
