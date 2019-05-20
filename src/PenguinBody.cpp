#include "../include/PenguinBody.hpp"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated)
                                                :Component(associated){

  speed = Vec2();//inicialiizando as variáveis
  linearSpeed = 0;
  angle = 0;
  // hp = (std::rand() % 6)*10 + 500;
  hp = 1500;

  std::shared_ptr<Sprite> penguinb_sprite(new Sprite(associated, PENGUINBODY_PATH));
  associated.AddComponent(penguinb_sprite);//cirando a sprite e adicionando ao vetor de components

  std::shared_ptr<Collider> penguinb_collider(new Collider(associated));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(penguinb_collider);

  player = this;//seta a variável de instância(player) com a instância da classe criada para que seja acessado por outros lugares no código

}

PenguinBody::~PenguinBody(){
  player = nullptr;//seta a variável de instância como nullptr, para que outras entidades saibam que o objeto foi deletado.
}


void PenguinBody::Start(){

  GameObject *penguinc_object = new GameObject();
  pcannon =  Game::GetInstance().GetState().AddObject(penguinc_object);
  std::shared_ptr<GameObject> penguin_cannon = pcannon.lock();

  penguin_cannon->box.x = associated.box.x;
  penguin_cannon->box.y = associated.box.y;

  std::weak_ptr<GameObject> weak_pbody = Game::GetInstance().GetState().GetObjectPtr(&associated);

  std::shared_ptr<PenguinCannon> penguin_c(new PenguinCannon(*penguin_cannon, weak_pbody));
  penguin_cannon->AddComponent(penguin_c);
}

void PenguinBody::Update(float dt){

  InputManager& input = InputManager::GetInstance();

  if (input.IsKeyDown(A_KEY)) {
    // std::cout << "A" << '\n';
    angle -= PENGUIN_ANGULAR_SPEED*dt;

  }
  if (input.IsKeyDown(D_KEY)) {
     // std::cout << "D" << '\n';
     angle += PENGUIN_ANGULAR_SPEED*dt;
  }

  associated.angleDeg = angle;

  if (input.IsKeyDown(W_KEY) && (linearSpeed <= PENGUIN_MAX_SPEED)) {//é definido uma velocidade máxima à qual a câmera pode acelerar
    // std::cout << "W" << '\n';
    if (linearSpeed < 0) {
      linearSpeed += 2*PENGUIN_DELTA_SPEED*dt;
    }
    linearSpeed += PENGUIN_DELTA_SPEED*dt;

  }
   else if (input.IsKeyDown(S_KEY) && (linearSpeed >= PENGUIN_MIN_SPEED)) {
     // std::cout << "S" << '\n';
     if (linearSpeed > 0) {
       linearSpeed -= 2*PENGUIN_DELTA_SPEED*dt;
     }
     linearSpeed -= PENGUIN_DELTA_SPEED*dt;

  } else {

    if (linearSpeed > 0){//com essa lógica a movimentação nao para instantâneamente, mas a velocidade diminui gradativamente até 0
      linearSpeed -= PENGUIN_DELTA_SPEED*dt;

    }
    else if (linearSpeed < 0){
      linearSpeed += PENGUIN_DELTA_SPEED*dt;

    }
    else{
      speed = Vec2();
    }
  }

  speed.x = linearSpeed;
  speed.y = 0;

  speed.Rotate(-angle*PI/180);
  associated.box.x += speed.x*dt;
  associated.box.y += speed.y*dt;

  if (hp <= 0) {
    hp = 0;
    associated.RequestDelete();
    Camera::Unfollow();

    // std::cout << "morreu" << '\n';

    GameObject *death_object = new GameObject();
    std::weak_ptr<GameObject> weak_death =  Game::GetInstance().GetState().AddObject(death_object);//
    std::shared_ptr<GameObject> death = weak_death.lock();

    std::shared_ptr<Sprite> death_sprite(new Sprite(*death, PENGUIN_DEATH_SPRITES, PENGUIN_DEATH_FRAMECOUNT, PENGUIN_DEATH_FRAMETIME, PENGUIN_DEATH_FRAMECOUNT*PENGUIN_DEATH_FRAMETIME));
    std::shared_ptr<Sound> death_sound(new Sound(*death, PENGUIN_DEATH_SOUND));

    death->box.x  = associated.box.x + associated.box.w/2 - death->box.w/2;
    death->box.y  = associated.box.y + associated.box.h/2 - death->box.h/2;
    death->AddComponent(death_sprite);
    death->AddComponent(death_sound);
    death_sound->Play(1);
    // std::cout << "isdead "<< death->IsDead() << '\n';

  }
}

void PenguinBody::Render(){

}

bool PenguinBody::Is(std::string type){
  return (type == "PenguinBody");
}
Vec2 PenguinBody::Position(){
  return (associated.box.GetCenter());
}


void PenguinBody::NotifyCollision(GameObject& other){

  std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

  if (  (bullet != nullptr) && bullet->targetsPlayer == true  && hp > 0) {
    // std::cout << "pinguin levou tiro" << '\n';
    hp -= bullet->GetDamage();
  }
}
