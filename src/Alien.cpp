#include "../include/Alien.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"



Alien::Alien(GameObject& associated, int nMinions)
                                                  :Component(associated){


  std::shared_ptr<Sprite> alien_sprite(new Sprite(associated, ALIEN_PATH));
  associated.AddComponent(alien_sprite);

  hp = 100;
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

}

void Alien::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  float alien_dist = 10000; //distância do alien

  // SDL_GetMouseState(&action.pos.x, &action.pos.y);
  // action.pos.x += Camera::pos.x;
  // action.pos.y += Camera::pos.y;

  if (input.KeyPress(LEFT_MOUSE_BUTTON)){
    // action.type = SHOOT;
    Alien::Action action(Alien::Action::SHOOT, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
    taskQueue.emplace(action);
  }
  if (input.KeyPress(RIGHT_MOUSE_BUTTON)) {
    // action.type = MOVE;
    Action action(Action::MOVE, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
    taskQueue.emplace(action);
    alien_dist = associated.box.x - input.GetMouseX();
  }

  if (!taskQueue.empty()){
  // while (!taskQueue.empty()) {
  // Action action = taskQueue.front();
  // Action::ActionType t;// = taskQueue.front().type;
  // int t;
    switch (taskQueue.front().type) {

      case Action::SHOOT:
        taskQueue.pop();
      break;

      case Action::MOVE:
        if (abs(alien_dist) < DISTANCE_RANGE) {
          speed.x = 0;
          speed.y = 0;
          taskQueue.pop();
        } else {
          speed.x = (alien_dist - associated.box.x)*ALIEN_SPEED;
          speed.y = (alien_dist - associated.box.y)*ALIEN_SPEED;
        }
        associated.box.x += speed.x*dt;
        associated.box.y += speed.y*dt;

      break;

      default:
      break;
    }

  }

}
void Alien::Render(){

}
bool Alien::Is(std::string type){
  return (type == "Alien");
}
// std::shared_ptr<GameObject> enemy = std::shared_ptr<GameObject> (new GameObject());//instancia um GameObject para o que vai ser colocado no vetor ObjectArray com os componentes do inimigo
//
// std::shared_ptr<Sound> enemy_sound(new Sound(*enemy, ENEMY_SOUND_PATH));
// std::shared_ptr<Face> enemy_face(new Face(*enemy));
//

//
// enemy->AddComponent(enemy_sprite);
// enemy->AddComponent(enemy_sound);
// enemy->AddComponent(enemy_face);

// objectArray.emplace_back(std::move(enemy));
