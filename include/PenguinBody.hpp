#pragma once

#include "Component.hpp"
#include "PenguinCannon.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "State.hpp"


#define PENGUINBODY_PATH "assets/img/penguin.png"
#define PENGUIN_DELTA_SPEED 150
#define PENGUIN_MAX_SPEED 500
#define PENGUIN_MIN_SPEED -500
#define PENGUIN_ANGULAR_SPEED 200
#define FRICTION 2

class PenguinCannon;

class PenguinBody : public Component {

private:

  std::weak_ptr<GameObject> pcannon;
  Vec2 speed;
  float linearSpeed;
  float angle;
  int hp;


public:
  PenguinBody(GameObject& associated);
  ~PenguinBody();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);

  PenguinBody* player;

};
