#include "../include/Camera.hpp"
#include "../include/InputManager.hpp"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;
int Camera::Parallax_aux_x;
int Camera::Parallax_aux_y;

void Camera::Follow(GameObject* newFocus){
  focus = newFocus;
}

void Camera::Unfollow(){
  focus = nullptr;
}

void Camera::Update(float dt){

  InputManager& input = InputManager::GetInstance();

  if (focus != nullptr) {
    pos.x = focus->box.x + focus->box.w - WINDOW_WIDTH/2;
    pos.y = focus->box.y + focus->box.h - WINDOW_HEIGHT/2;

  } else {

    if (input.IsKeyDown(LEFT_ARROW_KEY) && (speed.x <= MAX_SPEED_X)) {//é definido uma velocidade máxima à qual a câmera pode acelerar
      speed.x+=DELTA_SPEED;
    }
     else if (input.IsKeyDown(RIGHT_ARROW_KEY) && (speed.x >= MIN_SPEED_X)) {
      speed.x-=DELTA_SPEED;
    } else {

      if (speed.x > 0)//com essa lógica a movimentação nao para instantâneamente, mas a velocidade diminui até 0
        speed.x -= DELTA_SPEED;
      else if (speed.x < 0)
        speed.x+= DELTA_SPEED;
      else
        speed.x = 0;
    }

    if (input.IsKeyDown(DOWN_ARROW_KEY) && (speed.y >= MIN_SPEED_Y) ) {
      speed.y-=DELTA_SPEED;
    }
     else if (input.IsKeyDown(UP_ARROW_KEY) && (speed.y <= MAX_SPEED_Y)) {
      speed.y+=DELTA_SPEED;
    } else {

      if (speed.y > 0)//com essa lógica a movimentação n~ao para instantâneamente, mas a velocidade diminui até 0
        speed.y -= DELTA_SPEED;
      else if (speed.y < 0)
        speed.y+= DELTA_SPEED;
      else
        speed.y = 0;
    }
    pos.x += speed.x*dt;
    pos.y += speed.y*dt;

  }
}
void Camera::ParallaxUpdate(int layer, bool ParallaxEnd){

  if (!ParallaxEnd) {
    Parallax_aux_x = pos.x;
    Parallax_aux_y = pos.y;
    pos.x = pos.x*(1+layer);
    pos.y = pos.y*(1+layer);
  } else {
    pos.x = Parallax_aux_x;
    pos.y = Parallax_aux_y;
  }
}
