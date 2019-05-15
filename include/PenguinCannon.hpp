#pragma once

#include "Component.hpp"
#include "PenguinBody.hpp"

#define PENGUINCANNON_PATH "assets/img/penguin.png"

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

};
