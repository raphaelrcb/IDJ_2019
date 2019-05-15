#pragma once

#include "Component.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "State.hpp"

#define PENGUINBODY_PATH "assets/img/penguin.png"

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
