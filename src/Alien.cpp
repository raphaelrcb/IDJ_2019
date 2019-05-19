#include "../include/Alien.hpp"
#include "../include/Camera.hpp"
#include "../include/PenguinBody.hpp"


int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions)
                                                  :Component(associated),
                                                   state(RESTING){


  std::shared_ptr<Sprite> alien_sprite(new Sprite(associated, ALIEN_PATH));
  associated.AddComponent(alien_sprite);

  std::shared_ptr<Collider> alien_collider(new Collider(associated, {0.8, 0.8}));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(alien_collider);
  // hp = ( (rand() % 6) )*100.0 + 1000;//cria uma escala aleatória entre 1 e 1.5
  hp = 1500;

  // hp = (std::rand() % 6)*100 + 1000;
  this->nMinions = nMinions;
  this->alienCount++;
  speed.x = 0;
  speed.y = 0;

}

Alien::~Alien(){

  minionArray.clear();
  this->alienCount--;

}

void Alien::Start(){

  for (int i = 0; i < nMinions; i++) {
    GameObject *minion_object = new GameObject();
    std::weak_ptr<GameObject> weak_minion =  Game::GetInstance().GetState().AddObject(minion_object);//pega a função AddObject do state para adicionar o novo minion ao array de objetos
    std::shared_ptr<GameObject> minion = weak_minion.lock();

    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);//pega um ponteiro para o alien que vai ser guardados pelos minions (outra função de state)
    std::shared_ptr<Minion> minion_s(new Minion(*minion, weak_alien, (360.0/nMinions)*i));//divide o arco de 360 graus pela quantidade de minions desejada para que tenham a mesma distância entre si

    minion->box.x = 0;
    minion->box.y = 0;

    minion->AddComponent(minion_s);
    minionArray.emplace_back(weak_minion);//adiciona o novo minion ao array de minions
  }
}

void Alien::Update(float dt){

  // InputManager& input = InputManager::GetInstance();
  Vec2 alien_dist = Vec2(); //distância do alien

  associated.angleDeg += ALIEN_ANG_SPEED*dt;//sinal positivo faz o alien girar no sentido horário
  if (associated.angleDeg >= 359 && associated.angleDeg <= 361) {
    associated.angleDeg = 0;
  }

  // if (input.MousePress(LEFT_MOUSE_BUTTON)){
  //   Alien::Action action(Action::SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y);//cura a ação com o tipo a a posição aproproados
  //   taskQueue.emplace(action);//coloca na fila
  // }
  // if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
  //   Action action(Action::MOVE, input.GetMouseX() - (associated.box.w/2) - Camera::pos.x, input.GetMouseY() - (associated.box.h/2) - Camera::pos.y);
  //   taskQueue.emplace(action);
  // }

  // if (!taskQueue.empty()){

    switch (state) {

      if (PenguinBody::player != nullptr) {
        destination = PenguinBody::player->Position();
      }

      case RESTING:
        if (restTimer.Get() >= ALIEN_COOLDOWN) {
          if (PenguinBody::player != nullptr) {
            destination = PenguinBody::player->Position();
          }
          state = MOVING;
        }
        else {
          restTimer.Update(dt);
        }

      break;

      case MOVING:
        if ( (associated.box.GetCenter() - destination).Absolute() >  DISTANCE_RANGE)  {

          float movement = ALIEN_SPEED*dt;

          alien_dist = destination - associated.box.GetCenter();
          if (alien_dist.Absolute() > movement) {
            float angle = atan2(alien_dist.y, alien_dist.x);
            associated.box.x += movement*cos(angle);
            associated.box.y += movement*sin(angle);
          }
          else{
            associated.box.x = destination.x - associated.box.w/2;
            associated.box.y = destination.y - associated.box.h/2;
          }
        }
        else{

          Vec2 target = destination;
          Vec2 shoot_dist = Vec2();
          float min = std::numeric_limits<float>::max(); // pega o valor máximo em float para comparação de menor distância
          int prox_minion; //minion mais proximo do alvo

          for (unsigned int i = 0; i < minionArray.size(); i++) {

            shoot_dist = target - minionArray[i].lock()->box.GetVec2();//calcula a distancia do i-ésimo minion para o alvo
            if (  (shoot_dist).Absolute() < min ) {//se essa distância for menor que a ultima sava, guarda essa distância e o número do minion
              prox_minion = i;
              min = (shoot_dist).Absolute();
            }
          }

          std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>( minionArray[prox_minion].lock()->GetComponent("Minion"));

          if (minion != nullptr) {
            if (PenguinBody::player != nullptr) {
              minion->Shoot(target);//manda o minion atirar
            }
          }
          restTimer.Restart();
          state = RESTING;
        }

      break;
    }

  // }

  if (hp <= 0) {//se a vida do alien chegar a zero ou menos, ele morre e o objeto é deletado
    std::cout << "morreu" << '\n';
    hp = 0;

    GameObject *death_object = new GameObject();
    std::weak_ptr<GameObject> weak_death =  Game::GetInstance().GetState().AddObject(death_object);//
    std::shared_ptr<GameObject> death = weak_death.lock();

    std::shared_ptr<Sprite> death_sprite(new Sprite(*death, ALIEN_DEATH_SPRITES, 4, 0.1, 4*0.1));
    death->AddComponent(death_sprite);

    std::shared_ptr<Sound> death_sound(new Sound(*death, ALIEN_DEATH_SOUND));
    death->AddComponent(death_sound);

    death->box = associated.box;

    death_sound->Play(1);

    associated.RequestDelete();
  }
  // std::cout << hp << '\n';
}
void Alien::Render(){

}
bool Alien::Is(std::string type){
  return (type == "Alien");
}

void Alien::NotifyCollision(GameObject& other){

  std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(other.GetComponent("Bullet"));

  if (bullet != nullptr && bullet->targetsPlayer == false) {
    // std::cout << "alien colidiu com bullet" << '\n';
    hp -= bullet->GetDamage();
  }
}
