#include "../include/Alien.hpp"
#include "../include/Camera.hpp"



Alien::Alien(GameObject& associated, int nMinions)
                                                  :Component(associated){


  std::shared_ptr<Sprite> alien_sprite(new Sprite(associated, ALIEN_PATH));
  associated.AddComponent(alien_sprite);

  std::shared_ptr<Collider> alien_collider(new Collider(associated, {0.8, 0.8}));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(alien_collider);
  // hp = ( (rand() % 6) )*100.0 + 1000;//cria uma escala aleatória entre 1 e 1.5
  hp = 1500;

  // hp = (std::rand() % 6)*100 + 1000;
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

    minion->box.x = 0;
    minion->box.y = 0;

    minion->AddComponent(minion_s);
    minionArray.emplace_back(weak_minion);//adiciona o novo minion ao array de minions
  }
}

void Alien::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  Vec2 alien_dist = Vec2(); //distância do alien

  associated.angleDeg += ALIEN_ANG_SPEED*dt;//sinal positivo faz o alien girar no sentido horário
  if (associated.angleDeg >= 359 && associated.angleDeg <= 361) {
    associated.angleDeg = 0;
  }

  if (input.MousePress(LEFT_MOUSE_BUTTON)){
    Alien::Action action(Action::SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y);//cura a ação com o tipo a a posição aproproados
    taskQueue.emplace(action);//coloca na fila
  }
  if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
    Action action(Action::MOVE, input.GetMouseX() - (associated.box.w/2) - Camera::pos.x, input.GetMouseY() - (associated.box.h/2) - Camera::pos.y);
    taskQueue.emplace(action);
  }

  if (!taskQueue.empty()){

    switch (taskQueue.front().type) {

      case Action::MOVE:

        alien_dist = (taskQueue.front().pos - associated.box.GetVec2());//calcula a distância do alien para a posição destino
        speed = (   alien_dist/(  alien_dist.Absolute() )   )*(float)ALIEN_SPEED;//calcula a velocidade normalizada

        if (alien_dist.Absolute() < DISTANCE_RANGE) {// se o módulo da distância for menor que o range estabelecido para parada

          speed = Vec2();//o alien para de se mover
          taskQueue.pop();//retira a ação da fila

        } else {//se ainda não está no range

        associated.box.x += speed.x*dt;//desloca o alien com o passo de VELOCIDADE CALCULADA X TEMPO PASSADO NO FRAME
        associated.box.y += speed.y*dt;
        }
      break;

      case Action::SHOOT:
          float min = std::numeric_limits<float>::max(); // pega o valor máximo em float para comparação de menor distância
          int prox_minion; //minion mais proximo do alvo
          Vec2 shoot_dist = Vec2();
          for (unsigned int i = 0; i < minionArray.size(); i++) {

            shoot_dist = taskQueue.front().pos - minionArray[i].lock()->box.GetVec2();//calcula a distancia do i-ésimo minion para o alvo
            if (  (shoot_dist).Absolute() < min ) {//se essa distância for menor que a ultima sava, guarda essa distância e o número do minion
              prox_minion = i;
              min = (shoot_dist).Absolute();
            }
          }
          //o minion mais próximo atira
          std::shared_ptr<Minion> minion = std::dynamic_pointer_cast<Minion>( minionArray[prox_minion].lock()->GetComponent("Minion"));

          minion->Shoot(taskQueue.front().pos);//manda o minion atirar
          taskQueue.pop();//tira a ação da fila

      break;
    }

  }

  if (hp <= 0) {//se a vida do alien chegar a zero ou menos, ele morre e o objeto é deletado
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
