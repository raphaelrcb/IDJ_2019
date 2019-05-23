#pragma once

#include "State.hpp"
#include "Sprite.hpp"
#include "StageState.hpp"

#define TITLE_PATH "assets/img/title.jpg"

class TitleState : public State {

private:

public:

  TitleState();
  ~TitleState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
