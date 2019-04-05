#include "../include/GameObject.hpp"

GameObject::GameObject(){//inicializa IsDead como falso
  isDead = false;
}

GameObject::~GameObject(){
  // for (int i = components.size(); i > 0 ; i--) {
  //   components.erase(components.begin()+i);
  // }
  components.clear();
}

void GameObject::Update(float dt){
  for (unsigned int i = 0; i < components.size(); i++) {
    components[i]->Update(dt);
  }
}

void GameObject::Render(){
  for (unsigned int i = 0; i < components.size(); i++) {
    components[i]->Render();
  }
}

bool GameObject::IsDead(){
  return isDead;
}

void GameObject::RequestDelete(){
  isDead = true;
}

void GameObject::AddComponent(std::unique_ptr<Component> cpt){
  components.emplace_back(std::move(cpt));
}

void GameObject::RemoveComponent(std::unique_ptr<Component> cpt){
  // std::vector<int>::iterator cpt_iterator;      [&](std::unique_ptr<Component>& p) { return p.get() == cpt;}
  // auto cpt_iterator = std::find_if(components.begin(), components.end(),  [&](std::unique_ptr<Component>& p) { return p.get() == cpt;});//compara cpt com os valores de vecotr entre begin e end

  // std::vector<std::unique_ptr<Component>>::iterator cpt_iterator = std::find_if(components.begin(), components.end(), [&](std::unique_ptr<Component>& p) { return p.get() == cpt;});//compara cpt com os valores de vecotr entre begin e end
  auto const& cpt_iterator = std::find_if(components.begin(), components.end(), std::move(cpt));//compara cpt com os valores de vecotr entre begin e end


  if(cpt_iterator != components.end()) {//caso cpt esteja em components, o valor retornado é o iterador do elemento em components
    components.erase(std::remove(components.begin(), components.begin(), *cpt_iterator));//caso não encontre o elemento, o valor retornado é igual a end
  } else {
    std::cout << "the vector does not contain the component you are looking for" <<  std::endl;
  }
}

std::unique_ptr<Component> GameObject::GetComponent(std::string type){

  int exists = 0;
  unsigned int i;

  for (i = 0; i < components.size(); i++) {
    if (components[i]->Is(type)){
      exists = 1;
      i = components.size();
    }
  }
  if (exists == 1 ) {
    return std::move(components[i]);//components[i].get();
  } else {
    return std::unique_ptr<Component>(nullptr);
  }
}
