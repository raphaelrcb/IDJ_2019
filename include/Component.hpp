#include "string.h"
#include "GameObject.h"

class Component{
private:
public:
  Component(GameObject& associated);
  virtual ~Component();
  void virtual pure Update(float dt);
  void virtual pure Render();
  bool virtual pure Is(std::string type);
}
