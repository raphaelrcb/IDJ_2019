#include "../include/GameObject.hpp"
#include "Sound.hpp"

GameObject::GameObject(){//inicializa IsDead como falso
  isDead = false;
}

GameObject::~GameObject(){
  components.clear();//apaga e livbera os GameObject
}

void GameObject::Update(float dt){//chama a função Update de todos os componentes do objeto
  for (unsigned int i = 0; i < components.size(); i++) {
    components[i]->Update(dt);
  }
}

void GameObject::Render(){//chama a função Render de todos os componentes do objeto
  for (unsigned int i = 0; i < components.size(); i++) {
    components[i]->Render();
  }
}

bool GameObject::IsDead(){///////////////////////////////////////////checkpoint
  return isDead;
}

void GameObject::RequestDelete(){
  isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt){
  std::cout << "added component " << cpt->Is("Sound") <<'\n';

  components.emplace_back(std::move(cpt));//Adiciona um componente ao
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt){

  int it = -1;
  for (unsigned int i = 0; i < components.size(); i++) {
    if (components[i] == cpt) {
      it = i;
      components.erase(components.begin() + it);
      break;
    } else {
    std::cout << "the vector does not contain the component you are looking for" <<  std::endl;
    }
  }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type){

  for (unsigned int i = 0; i < components.size(); i++) {
    if (components[i]->Is(type)){
      return components[i];//components[i].get();
    }
  }
  std::cout << "return null" << '\n';
  return (nullptr);
}