#pragma once

#include <iostream>

class Sound : public Component {
private:
  int hitpoints;
public:
  Face(GameObject& associated);
  void Damage(int damage);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
