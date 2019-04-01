#include "../include/GameObject.hpp"

GameObject::GameObject(){//inicializa IsDead como falso
  IsDead = false;
}

GameObject::~GameObject(){
  for (int i = components.size(); i > 0 ; i--) {
    components.erase(components.begin()+i);
  }
  components.clear();
}

void GameObject::Update(float dt){
  for (int i = 0; i < components.size(); i++) {
    components[i].Component::Update(dt);
  }
}

void GameObject::Render(){
  for (int i = 0; i < components.size(); i++) {
    components[i].Component::Render();
  }
}

bool GameObject::IsDead(){
  return IsDead;
}

void GameObject::RequestDelete(){
  IsDead = true;
}

void GameObject::AddComponent(Component* cpt){
  component.push_back(cpt)
}

void GameObject::RemoveComponent(Component* cpt){

  cpt_iterator = std::find(components.begin(), components.end(), cpt);//compara cpt com os valores de vecotr entre begin e end
  if(cpt_iterator != components.end()) {//caso cpt esteja em components, o valor retornado é o iterador do elemento em components
    components.erase(components.begin()+cpt_iterator);//caso não encontre o elemento, o valor retornado é igual a end
  } else {
    std::cout << "the vector does not contain " << cpt <<  std::endl;
  }
}

Component* GameObject::Component(std::string type){
  type_iterator = std::find(components.begin(), components.end(), type);
  if(type_iterator != components.end()) {
    return *(components[components.begin()+type_iterator])//components.erase(components.begin()+type_iterator);
  } else {
    std::cout << "The components does not have the type  " << type <<  std::endl;
    return nullptr;
  }
}
