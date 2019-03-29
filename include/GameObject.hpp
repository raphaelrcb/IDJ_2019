#include "string.h"
#include "Component.hpp"

class GameObject{
private:
  std::std::vector<Component*> components;
  bool IsDead
public:
  GameObject();
  ~GameObject();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(std::string type);
  Rect box;
}
