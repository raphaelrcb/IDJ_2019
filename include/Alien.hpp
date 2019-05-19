#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string.h>
#include <queue>
#include <limits>
#include "Component.hpp"
#include "GameObject.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "Minion.hpp"
#include "Bullet.hpp"
#include "State.hpp"
#include "Game.hpp"

#define ALIEN_PATH "assets/img/alien.png"
#define ALIEN_SPEED 400 //valor da variação de velocidade dado ao objeto caso ele se movimente
#define ALIEN_ANG_SPEED 30
#define DISTANCE_RANGE 200
#define N_MINIONS 5
#define ALIEN_COOLDOWN 0.3

#define ALIEN_DEATH_SPRITES "assets/img/aliendeath.png"
#define ALIEN_DEATH_SOUND "assets/audio/boom.wav"
#define ALIEN_DEATH_FRAMECOUNT 4
#define ALIEN_DEATH_FRAMETIME 0.2

class Alien : public Component {

private:
  Vec2 speed;
  int hp;
  int nMinions;
  std::vector< std::weak_ptr<GameObject> > minionArray;

  enum AlienState {MOVING, RESTING};
  AlienState state;
  Timer restTimer;
  Vec2 destination;

public:
  Alien(GameObject& associated, int nMinions);
  ~Alien();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject& other);

  static int alienCount;

};
