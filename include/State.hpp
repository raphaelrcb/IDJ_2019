#pragma once

#include <ctime>
#include <cstdlib>
#include <stdbool.h>

// #include "Component.hpp"
#include "GameObject.hpp"
// #include "Sound.hpp"
// #include "Sprite.hpp"
// #include "TileMap.hpp"
// #include "CameraFollower.hpp"
// #include "Music.hpp"
// #include "InputManager.hpp"
// #include "Alien.hpp"
// #include "PenguinBody.hpp"
// #include "Collider.hpp"

class State {

protected:

  void StartArray();
  virtual void UpdateArray(float dt);
  virtual void RenderArray();

  bool popRequested;
  bool quitRequested;
  bool started;

  std::vector< std::shared_ptr<GameObject> > objectArray;

public:

  State();
  virtual ~State();

  virtual void LoadAssets() = 0;
  virtual void Update(float dt) = 0;
  virtual void Start() = 0;
  virtual void Render() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
  virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

  bool PopRequested();
  bool QuitRequested();

};
