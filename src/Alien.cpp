#include "../include/Alien.hpp"
#include "../include/Camera.hpp"



Alien::Alien(GameObject& associated, int nMinions)
                                                  :Component(associated){


  std::shared_ptr<Sprite> alien_sprite(new Sprite(associated, ALIEN_PATH));
  associated.AddComponent(alien_sprite);

  hp = 100;
  this->nMinions = nMinions;
  speed.x = 0;
  speed.y = 0;

}
Alien::Action::Action(ActionType type, float x, float y){

  this->type = type;
  this->pos.x = x;
  this->pos.y = y;

}

Alien::~Alien(){

  minionArray.clear();

}

void Alien::Start(){

  for (int i = 0; i < nMinions; i++) {
    GameObject *minion_object = new GameObject();
    std::weak_ptr<GameObject> weak_minion =  Game::GetInstance().GetState().AddObject(minion_object);//pega a função AddObject do state para adicionar o novo minion ao array de objetos
    std::shared_ptr<GameObject> minion = weak_minion.lock();

    std::weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);//pega um ponteiro para o alien que vai ser guardados pelos minions (outra função de state)
    std::shared_ptr<Minion> minion_s(new Minion(*minion, weak_alien, (360.0/nMinions)*i));//divide o arco de 360 graus pela quantidade de minions desejada para que tenham a mesma distância entre si

    minion->AddComponent(minion_s);
    minionArray.emplace_back(weak_minion);//adiciona o novo minion ao array de minions
  }
}

void Alien::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  Vec2 alien_dist = Vec2(); //distância do alien
  // std::cout << dt << '\n';

  associated.angleDeg += ALIEN_ANG_SPEED*dt;//sinal positivo faz o alien girar no sentido horário
  if (associated.angleDeg >= 359 && associated.angleDeg <= 361) {
    associated.angleDeg = 0;
  }

  if (input.MousePress(LEFT_MOUSE_BUTTON)){
    // action.type = SHOOT;
    Alien::Action action(Action::SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y);
    taskQueue.emplace(action);
  }
  if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
    // action.type = MOVE;
    Action action(Action::MOVE, input.GetMouseX() - (associated.box.w/2) - Camera::pos.x, input.GetMouseY() - (associated.box.h/2) - Camera::pos.y);
    taskQueue.emplace(action);
    // alien_dist = taskQueue.front().pos - associated.box.Get();
  }

  if (!taskQueue.empty()){

    switch (taskQueue.front().type) {

      case Action::MOVE:

        alien_dist = (taskQueue.front().pos - associated.box.Get());
        speed = (   alien_dist/(  alien_dist.Absolute() )   )*(float)ALIEN_SPEED;

        if ((alien_dist.x > -DISTANCE_RANGE) && (alien_dist.x < DISTANCE_RANGE) &&
            (alien_dist.y > -DISTANCE_RANGE) && (alien_dist.y < DISTANCE_RANGE) ) {

          speed = Vec2();
          taskQueue.pop();
          // std::cout << "Chegou!!" << '\n';

        } else {

        associated.box.x += speed.x*dt;
        associated.box.y += speed.y*dt;
        }
      break;

      case Action::SHOOT:

          int prox_minion = (rand() % nMinions );

          // std::weak_ptr<Component> cpt;
          // std::shared_ptr<Component> shared = cpt.lock();
          // std::vector< std::shared_ptr<Component> > minions;
          // std::cout << "erro aqui 1" << '\n';
          //
          // for (int i = 0; i < nMinions; i++){
          //   shared = associated.GetComponent("Minion");
          //   ( ( (minions).push_back(shared) ) );
          // }

          // std::cout << "erro aqui 2" << '\n';
          std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>( minionArray[prox_minion].lock()->GetComponent("Minion"));
          minion->Shoot(taskQueue.front().pos);
          // std::cout << "erro aqui 2" << '\n';
          taskQueue.pop();

      break;
    }

  }

}
void Alien::Render(){

}
bool Alien::Is(std::string type){
  return (type == "Alien");
}
