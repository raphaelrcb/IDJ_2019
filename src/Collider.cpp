#include "../include/Collider.hpp"


Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset):Component(associated){
  this->scale = scale;
  this->offset = offset;
}

void Collider::Update(float dt){
  this->box = associated.box;//a box do collider recebe uma cópia do associated
  this->box.w = this->box.w*scale.x;//multiplica a largura e a altura pela escala
  this->box.y = this->box.h*scale.y;

  this->box.x = associated.box.x + associated.box.w/2 - this->box.w/2;//realinha o centro da box do collider com a do associated
  this->box.y = associated.box.y + associated.box.h/2 - this->box.h/2;

  offset.Rotate(associated.angleDeg);//rotaciona o offset com o mesmo angulo do associated

  this->box.x += offset.x;//soma o offset à box do collider
  this->box.y += offset.y;

}
void Collider::Render(){

}
bool Collider::Is(std::string type){
  return (type == "Collider");
}
void Collider::SetScale(Vec2 scale){
  this->scale = scale;
}
void Collider::SetOffset(Vec2 offset){
  this->offset = offset;
}
