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
  Vec2 alien_dist = Vec2(); //distância do alien
  // std::cout << dt << '\n';

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

      case Action::SHOOT:
        taskQueue.pop();
      break;

      case Action::MOVE:

        alien_dist = (taskQueue.front().pos - associated.box.Get());
        speed = (   alien_dist/(  alien_dist.Absolute() )   )*(float)ALIEN_SPEED;

        if ((alien_dist.x > -DISTANCE_RANGE) && (alien_dist.x < DISTANCE_RANGE) &&
            (alien_dist.y > -DISTANCE_RANGE) && (alien_dist.y < DISTANCE_RANGE) ) {

          speed = Vec2();
          taskQueue.pop();
          std::cout << "Chegou!!" << '\n';

        } else {

        associated.box.x += speed.x*dt;
        associated.box.y += speed.y*dt;

      }
      break;
    }

  }

}
void Alien::Render(){

}
bool Alien::Is(std::string type){
  return (type == "Alien");
}
