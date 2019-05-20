#pragma once

#include "Component.hpp"
#include "PenguinBody.hpp"
#include "Bullet.hpp"
#include "Timer.hpp"

#define PENGUINCANNON_PATH "assets/img/cubngun.png"
#define PENGUIN_BULLET_PATH "assets/img/penguinbullet.png"
#define PENGUIN_BULLET_FRAMECOUNT 4
#define PENGUIN_BULLET_FRAMETIME 2
#define PENGUIN_BULLET_RANGE 1500
#define CANNON_COOLDOWN 0.5
// #define PENGUIN_BULLET_PATH "assets/img/penguinbullet.png"
// #define PENGUIN_BULLET_FRAMECOUNT 4
// #define PENGUIN_BULLET_FRAMETIME 1/PENGUIN_BULLET_FRAMECOUNT


class PenguinBody;

class PenguinCannon : public Component {

private:

  std::weak_ptr<GameObject> pbody;
  float angle;

public:
  PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot();
  void NotifyCollision(GameObject& other);


};
