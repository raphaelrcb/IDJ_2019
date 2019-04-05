#include "../include/GameObject.hpp"

GameObject::GameObject(){//inicializa IsDead como falso
  isDead = false;
}

GameObject::~GameObject(){
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

bool GameObject::IsDead(){///////////////////////////////////////////checkpoint
  return isDead;
}

void GameObject::RequestDelete(){
  isDead = true;
}

void GameObject::AddComponent(Component* cpt){
  components.emplace_back(std::move(cpt));
}

void GameObject::RemoveComponent(Component* cpt){
  // std::vector<Component*>::iterator cpt_iterator;
  // auto cpt_iterator = std::find_if(components.begin(), components.end(),  [&](std::unique_ptr<Component>& p) { return p.get() == cpt;});//compara cpt com os valores de vecotr entre begin e end
  // std::vector<std::unique_ptr<Component>>::iterator cpt_iterator = std::find_if(components.begin(), components.end(), [&](std::unique_ptr<Component>& p) { return p.get() == cpt;});//compara cpt com os valores de vecotr entre begin e end
  // std::vector<Component*>::iterator cpt_iterator = std::find(components.begin(), components.end(), cpt);//compara cpt com os valores de vecotr entre begin e end
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


  // if(/*it != -1*/cpt_iterator != components.end()) {//caso cpt esteja em components, o valor retornado é o iterador do elemento em components
    // components.erase(std::find(components.begin(), components.end(), cpt));//caso não encontre o elemento, o valor retornado é igual a end
}

Component* GameObject::GetComponent(std::string type){

  for (unsigned int i = 0; i < components.size(); i++) {
    if (components[i]->Is(type)){
      return components[i];//components[i].get();
    }
  }
  std::cout << "return null" << '\n';
  return (nullptr);
}
