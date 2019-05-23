#pragma once

#include "State.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "CameraFollower.hpp"
#include "Music.hpp"
#include "InputManager.hpp"
#include "Alien.hpp"
#include "PenguinBody.hpp"
#include "Collider.hpp"

#define PI 3.14159265359
#define BG_PATH "assets/img/ocean.jpg"
#define TILESET_PATH "assets/img/tileset.png"
#define TILEMAP_PATH "assets/map/tileMap.txt"
#define MUSIC_PATH "assets/audio/stageState.ogg"
// #define N_MINIONS 5

class StageState : public State {

private:

  TileSet* tileSet;
  Music backgroundMusic;

public:

  StageState();
  ~StageState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
