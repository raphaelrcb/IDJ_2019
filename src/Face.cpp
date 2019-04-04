#include "../include/Face.hpp"

Face::Face(GameObject& associated):Component(associated){
  hitpoints = 50;
}
void Face::Damage(int damage){
  hitpoints-=damage;

  if (hitpoints <= 0) {
    associated.RequestDelete();
    if (associated.GetComponent("Sound") != nullptr) {
      associated.Play(1);
    }
  }
}

void Face::Update(float dt){
}

void Face::Render(){
}

bool Face::Is(std::string type){
  if (type == "Face") {
    return true;
  } else {
    return false;
  }
}
