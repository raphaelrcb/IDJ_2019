#include "../include/Minion.hpp"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) :
                                                                                                  Component(associated),
                                                                                                  alienCenter(alienCenter){


  std::shared_ptr<Sprite> minion_sprite(new Sprite(associated, MINION_PATH));
  associated.AddComponent(minion_sprite);

  this->alienCenter = alienCenter;//ponteiro para o alien
  std::shared_ptr<GameObject> alien = alienCenter.lock();//transforma em shared ponter para se fazerem operações com ele

  Vec2 origin_dist = Vec2(150,0);
  arc = arcOffsetDeg*PI/180;//converte o arcOffsetDeg para radianos

  if (alien != nullptr) {//se tem um alien, inicia com o minion já em uma posição rotacionada

    origin_dist.Rotate(arc);//rotaciona com o arco dado
    origin_dist += (alien->box).GetCenter();//soma à posição do centro do alien já que o minion orbita o alien
    origin_dist.x -= associated.box.w/2;//corrige para pegar o centro do minion
    origin_dist.y -= associated.box.h/2;
    associated.box += origin_dist;//atualiza a posição do minion com a distância deslocada para que os próximos não sejam impressos em cima
  }
  else {
    associated.RequestDelete();//se não existe alien, deleta o minion
  }

}

void Minion::Update(float dt){

  Vec2 origin_dist = Vec2(150,0);
  std::shared_ptr<GameObject> alien = alienCenter.lock();

  if (alien != nullptr) {

    origin_dist.Rotate(arc);//rotaciona com o arco dado
    origin_dist += (alien->box).GetCenter();//soma à posição do centro do alien já que o minion orbita o alien
    origin_dist.x -= associated.box.w/2;//corrige para pegar o centro do minion
    origin_dist.y -= associated.box.h/2;

    arc += V_ANG_MINION*dt;//atualiza o arco para se mover com a velocidade angular definida no próximo frame
    associated.box = origin_dist;//atualiza a posição do minion

  }
  else {
    associated.RequestDelete();
  }
}

void Minion::Render(){

}

bool Minion::Is(std::string type){
  return (type == "Minion");
}

void Minion::Shoot(Vec2 target){

}
