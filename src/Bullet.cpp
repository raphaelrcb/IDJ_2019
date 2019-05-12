#include "../include/Bullet.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite):
                                                                                                                      Component(associated){

  std::shared_ptr<Sprite> bullet_sprite(new Sprite(associated, sprite));
  associated.AddComponent(bullet_sprite);
  this->distanceLeft = maxDistance;// no inicio a distancia restante é igual a máxima

  this->speed.x = speed*cos(angle);//define o vetor velocidade de acordo com o valor passado para o consturtor
  this->speed.y = speed*sin(angle);
  // std::cout <<"max " << maxDistance << '\n';

  this->damage = damage;//define odanode acordo com o passado pelo construtor

  associated.angleDeg = angle*180/PI;
}


void Bullet::Update(float dt){

  associated.box += speed*dt; // o passo em que a bullet anda o frame é calculado pela volocidade vezes o tempo em que passou entre os frames
  // std::cout << distanceLeft << '\n';
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
