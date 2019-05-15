#include "../include/PenguinCannon.hpp"


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody):Component(associated){

  pbody = penguinBody;//inicializando as variáveis
  angle = 0;

  std::shared_ptr<Sprite> penguinc_sprite(new Sprite(associated, PENGUINCANNON_PATH));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(penguinc_sprite);
}


void PenguinCannon::Update(float dt){

}
void PenguinCannon::Render(){

}
bool PenguinCannon::Is(std::string type){
  return (type == "PenginCannon");
}
void PenguinCannon::Shoot(){

}
