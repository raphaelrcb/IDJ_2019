#pragma once

#include <ctime>
#include <cstdlib>

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
#include "CameraFollower.hpp"
#include "Music.hpp"
#include "InputManager.hpp"
#include "Alien.hpp"
#include "PenguinBody.hpp"


#define PI 3.14159265359
#define BG_PATH "assets/img/ocean.jpg"
#define TILESET_PATH "assets/img/tileset.png"
#define TILEMAP_PATH "assets/map/tileMap.txt"
#define MUSIC_PATH "assets/audio/stageState.ogg"
#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"
#define N_MINIONS 4

class State{

private:
  // Sprite bg;
  Music music;

  bool quitRequested;
  bool started;
  std::vector< std::shared_ptr<GameObject> > objectArray;

public:

  State();
  ~State();

  std::weak_ptr<GameObject> AddObject(GameObject* go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

  void Start();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};
