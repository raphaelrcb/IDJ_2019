#include "../include/Minion.hpp"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) :
                                                                                                  Component(associated),
                                                                                                  alienCenter(alienCenter){

  std::shared_ptr<Sprite> minion_sprite(new Sprite(associated, MINION_PATH));

  float random_scale = 1 + ( (rand() % 6) )/10.0;//cria uma escala aleatória entre 1 e 1.5
  minion_sprite->SetScaleX(random_scale, random_scale);//manda essa escala para o minion

  std::shared_ptr<Collider> minion_collider(new Collider(associated, {0.85, 0.85}));//criando a sprite e adicionando ao vetor de Components

  associated.AddComponent(minion_sprite);
  associated.AddComponent(minion_collider);

  this->alienCenter = alienCenter;//ponteiro para o alien
  std::shared_ptr<GameObject> alien = alienCenter.lock();//transforma em shared ponter para se fazerem operações com ele

  Vec2 origin_dist = Vec2(MINION_RADIUS,0);
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

  Vec2 origin_dist = Vec2(MINION_RADIUS,0);
  std::shared_ptr<GameObject> alien = alienCenter.lock();

  associated.angleDeg = -arc*180/PI;//sinal negativo faz o minion girar no sentido anti-horário

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

    GameObject *death_object = new GameObject();
    std::weak_ptr<GameObject> weak_death =  Game::GetInstance().GetCurrentState().AddObject(death_object);//
    std::shared_ptr<GameObject> death = weak_death.lock();

    std::shared_ptr<Sprite> death_sprite(new Sprite(*death, MINION_DEATH_SPRITES, MINION_DEATH_FRAMECOUNT, MINION_DEATH_FRAMETIME, MINION_DEATH_FRAMECOUNT*MINION_DEATH_FRAMETIME));
    death->AddComponent(death_sprite);

    death->box = associated.box;

  }

}

void Minion::Render(){

}

bool Minion::Is(std::string type){
  return (type == "Minion");
}

void Minion::Shoot(Vec2 target){

  GameObject *bullet_object = new GameObject();
  std::weak_ptr<GameObject> weak_bullet =  Game::GetInstance().GetCurrentState().AddObject(bullet_object);//pega a função AddObject do state para adicionar o novo bullet ao array de objetos
  std::shared_ptr<GameObject> bullet = weak_bullet.lock();
  // Vec2 shoot_dist = (target - associated.box.GetCenter());// a distância do tiro é o vetor resultante da diferença da posição do tiro e da posição do minion que vai atirar

  bullet->box.x = associated.box.x + associated.box.w/2;//a posição em que a bullet sai é a mesma possição so minion
  bullet->box.y = associated.box.y + associated.box.h/2;

  float angle = atan2(target.y - associated.box.y - associated.box.h/2, target.x - associated.box.x - associated.box.w/2);

  std::shared_ptr<Bullet> bullet_s(new Bullet(*bullet, angle, BULLET_SPEED, BULLET_DAMAGE, MINION_BULLET_RANGE, MINION_BULLET_PATH, MINION_BULLET_FRAMECOUNT, MINION_BULLET_FRAMETIME, true));//divide o arco de 360 graus pela quantidade de bullets desejada para que tenham a mesma distância entre si
  bullet->AddComponent(bullet_s);

  // bullet->box.x -= bullet->box.w/2;//compensa o tamanho da bullet na posição dela
  // bullet->box.y -= bullet->box.h/2;

}

void Minion::NotifyCollision(GameObject& other){

  std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

  if (bullet != nullptr && bullet->targetsPlayer == false) {
  }
}
