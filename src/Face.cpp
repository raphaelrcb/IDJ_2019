#include "../include/Face.hpp"

Face::Face(GameObject& associated):Component(associated){
  hitpoints = 1;
}
void Face::Damage(int damage){
  hitpoints-=damage;

  if (hitpoints <= 0) {

    Component* cpt = associated.GetComponent("Sound");
    if (cpt != nullptr){
      Sound* cpt_sound = dynamic_cast<Sound*>(cpt);
      cpt_sound->Play(1);
      // associated.Play(1);
    }
    associated.RequestDelete();
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
