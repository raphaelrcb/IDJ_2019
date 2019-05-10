#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string.h>
#include <queue>
#include "Component.hpp"
#include "GameObject.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "Minion.hpp"
#include "State.hpp"
#include "Game.hpp"

#define ALIEN_PATH "assets/img/alien.png"
#define ALIEN_SPEED 200 //valor da variação de velocidade dado ao objeto caso ele se movimente
#define DISTANCE_RANGE 5
#define N_MINIONS 4

class Alien : public Component {

private:
  Vec2 speed;
  int hp;
  int nMinions;

  class Action{
  public:
    enum ActionType{
      MOVE,
      SHOOT
    };
    Action(ActionType type, float x, float y);

    ActionType type;
    Vec2 pos;
  };

  std::queue<Action> taskQueue;
  std::vector< std::weak_ptr<GameObject> > minionArray;

public:
  Alien(GameObject& associated, int nMinions);
  ~Alien();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);

};
