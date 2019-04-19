#include "../include/Face.hpp"
#include "InputManager.hpp"

Face::Face(GameObject& associated):Component(associated){
  hitpoints = 1;
}

void Face::Damage(int damage){
  hitpoints-=damage;
  // std::cout << "damage2" << '\n';
  if (hitpoints <= 0) {

    std::shared_ptr<Component> cpt = associated.GetComponent("Sound");

    if (cpt != nullptr){
      (std::dynamic_pointer_cast<Sound>(cpt))->Play(1);
      associated.RequestDelete();
    }
  }
}

void Face::Update(float dt){

  InputManager& input = InputManager::GetInstance();

  if (input.MousePress(LEFT_MOUSE_BUTTON)) {
    if(associated.box.Contains( (float)input.GetMouseX(), (float)input.GetMouseY() ) ) {
        // Aplica dano
        // std::cout << "damage" << '\n';
        Damage(std::rand() % 10 + 10);
    }
  }
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
