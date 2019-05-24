#pragma once

#include "State.hpp"
#include "Sprite.hpp"
#include "StageState.hpp"
#include "Text.hpp"

class EndState : public State {

private:

  Music backgroundMusic;

public:

  EndState();
  ~EndState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
