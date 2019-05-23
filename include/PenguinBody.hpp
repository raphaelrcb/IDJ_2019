#pragma once

#include "Component.hpp"
#include "PenguinCannon.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "State.hpp"
#include "Sound.hpp"


#define PENGUINBODY_PATH "assets/img/penguin.png"
#define PENGUIN_DELTA_SPEED 300
#define PENGUIN_MAX_SPEED 400
#define PENGUIN_MIN_SPEED -400
#define PENGUIN_ANGULAR_SPEED 200
#define FRICTION 200

#define PENGUIN_DEATH_SPRITES "assets/img/penguindeath.png"
#define PENGUIN_DEATH_SOUND "assets/audio/boom.wav"
#define PENGUIN_DEATH_FRAMECOUNT 5
#define PENGUIN_DEATH_FRAMETIME 0.2


class PenguinCannon;

class PenguinBody : public Component {

private:

  std::weak_ptr<GameObject> pcannon;
  Vec2 speed;
  float linearSpeed;
  float angle;
  int hp;


public:
  PenguinBody(GameObject& associated);
  ~PenguinBody();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject& other);
  Vec2 Position();

  static PenguinBody* player;

};
