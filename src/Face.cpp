#include "../include/Face.hpp"

Face::Face(GameObject& associated):Component(associated){
  hitpoints = 1;
}
void Face::Damage(int damage){
  hitpoints-=damage;
  std::cout << "damage2" << '\n';
  if (hitpoints <= 0) {

    // std::shared_ptr<Sound> cpt_sound = std::dynamic_pointer_cast<Sound>(associated.GetComponent("Sound"));
    std::shared_ptr<Component> cpt = associated.GetComponent("Sound");
    // std::cout << "cpt " << cpt->Is("Sound") <<'\n';
    // if (cpt_sound != nullptr){
    if (cpt != nullptr){
      // std::shared_ptr<Sound> cpt_sound = std::dynamic_pointer_cast<Sound>(cpt);
      // std::cout << "cpt_sound " << cpt_sound->Is("Sound") <<'\n';
      // std::cout << "cpt " << cpt_sound << '\n';
      (std::dynamic_pointer_cast<Sound>(cpt))->Play(1);
      associated.RequestDelete();
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
