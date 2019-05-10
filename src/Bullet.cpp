#include "../include/Bullet.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite):
                                                                                                                      Component(associated){

  std::shared_ptr<Sprite> bullet_sprite(new Sprite(associated, sprite));
  associated.AddComponent(bullet_sprite);

  this->distanceLeft = maxDistance;

  this->speed.x = speed*cos(angle);
  this->speed.y = speed*sin(angle);

  this->damage = damage;
}


void Bullet::Update(float dt){

  associated.box += speed*dt;
  distanceLeft -= (speed*dt).Absolute();

  if (distanceLeft <= 0 ) {
    associated.RequestDelete();
  }

}

void Bullet::Render(){

}

bool Bullet::Is(std::string type){
    return (type == "Bullet");
}

int Bullet::GetDamage(){
  return damage;
}
