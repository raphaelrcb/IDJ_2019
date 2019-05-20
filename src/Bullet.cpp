#include "../include/Bullet.hpp"
#define PI 3.14159265359

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer):
                                                                                                                      Component(associated){

  std::shared_ptr<Sprite> bullet_sprite(new Sprite(associated, sprite, frameCount, frameTime));
  associated.AddComponent(bullet_sprite);

  std::shared_ptr<Collider> bullet_collider(new Collider(associated));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(bullet_collider);

  this->distanceLeft = maxDistance;// no inicio a distancia restante é igual a máxima
  this->targetsPlayer = targetsPlayer;

  this->speed.x = speed*cos(angle);//define o vetor velocidade de acordo com o valor passado para o consturtor
  this->speed.y = speed*sin(angle);
  // std::cout <<"max " << maxDistance << '\n';

  this->damage = damage;//define odanode acordo com o passado pelo construtor
  associated.angleDeg = angle*180/PI;

}


void Bullet::Update(float dt){

  associated.box += speed*dt; // o passo em que a bullet anda o frame é calculado pela volocidade vezes o tempo em que passou entre os frames
  distanceLeft -= (speed*dt).Absolute(); //diminui esse passo da distância restante

  if (distanceLeft <= 0 ) {
    associated.RequestDelete();//se a distância restante for igual ou menor que zero , chegou no alvo e a bullet é deletada
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

void Bullet::NotifyCollision(GameObject& other){

  if ((other.GetComponent("Alien") || other.GetComponent("Minion")) && targetsPlayer == false) {
    associated.RequestDelete();
  }

  if (other.GetComponent("PenguinBody") && targetsPlayer == true) {
    associated.RequestDelete();
  }
}
