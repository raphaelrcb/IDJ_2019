#include "Component.hpp";

class CameraFollower : public Component{

private:

public:

  CameraFollower(GameObject& go)

  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
