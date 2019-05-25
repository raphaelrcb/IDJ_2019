#include "../include/PenguinCannon.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody):Component(associated){

  pbody = penguinBody;//inicializando as variáveis
  angle = 0;

  std::shared_ptr<Sprite> penguinc_sprite(new Sprite(associated, PENGUINCANNON_PATH));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(penguinc_sprite);

  std::shared_ptr<Collider> penguinc_collider(new Collider(associated));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(penguinc_collider);
}

void PenguinCannon::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  static Timer cooldown;

  Vec2 mouse = Vec2(input.GetMouseX(), input.GetMouseY());
  std::shared_ptr<GameObject> penguin_body = pbody.lock();

  if (penguin_body == nullptr) {
    associated.RequestDelete();
  }
  else {
    associated.box.x = penguin_body->box.x + penguin_body->box.w/2 - associated.box.w/2;
    associated.box.y = penguin_body->box.y + penguin_body->box.h/2 - associated.box.h/2;
    angle = atan2(mouse.y - (associated.box.y + associated.box.h/2) - Camera::pos.y, mouse.x - (associated.box.x + associated.box.w/2)  - Camera::pos.x);
    associated.angleDeg = angle*180/PI;

    cooldown.Update(dt);
    if (input.MousePress(LEFT_MOUSE_BUTTON)){
      if (cooldown.Get() > CANNON_COOLDOWN) {
        cooldown.Restart();
        Shoot();
      }
    }
  }
}

void PenguinCannon::Render(){
}

bool PenguinCannon::Is(std::string type){
  return (type == "PenginCannon");
}

void PenguinCannon::Shoot(){

  GameObject *bullet_object = new GameObject();
  std::weak_ptr<GameObject> weak_bullet =  Game::GetInstance().GetCurrentState().AddObject(bullet_object);//pega a função AddObject do state para adicionar o novo bullet ao array de objetos
  std::shared_ptr<GameObject> bullet = weak_bullet.lock();

  bullet->box.x = associated.box.x + associated.box.w/2 + cos(angle)*associated.box.w/2 + cos(angle)*associated.box.h/2;
  bullet->box.y = associated.box.y + associated.box.h/2 + sin(angle)*associated.box.w/2 + sin(angle)*associated.box.h/2;
  //coloca o posição da bullet no ponto em que o tiro vai sair, que é a ponta do canhão


  std::shared_ptr<Bullet> bullet_s(new Bullet(*bullet, angle, PENGUIN_BULLET_SPEED, BULLET_DAMAGE, PENGUIN_BULLET_RANGE, PENGUIN_BULLET_PATH, PENGUIN_BULLET_FRAMECOUNT, PENGUIN_BULLET_FRAMETIME, false));//divide o arco de 360 graus pela quantidade de bullets desejada para que tenham a mesma distância entre si
  bullet->AddComponent(bullet_s);

  bullet->box.x -= bullet->box.w/2;//compensa o tamanho da bullet na posição dela
  bullet->box.y -= bullet->box.h/2;
}

void PenguinCannon::NotifyCollision(GameObject& other){

  std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

    if (  (bullet != nullptr) && bullet->targetsPlayer == true  ) {
    }
}
