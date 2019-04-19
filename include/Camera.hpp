#include "GameObject.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define DELTA_SPEED 100
#define MAX_SPEED_X 300
#define MIN_SPEED_X -300
#define MAX_SPEED_Y 300
#define MIN_SPEED_Y -300

class Camera{

private:

  static GameObject* focus;

public:

  static void Follow(GameObject* newFocus);
  static void Unfollow();
  static void Update(float dt);

  static Vec2 pos;
  static Vec2 speed;
};
