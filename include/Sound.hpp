#include "Component.h"
#include "string.h"

class Sound : public Component {
private:
  Mix_Chunk* chunk;
  int channel;
public:
  Sound(GameObject& associated);
  Sound(GameObject& associated, std::string file);
  ~Sound();
  void Play(int times = 1);
  void Stop();
  void Open(std::string file);
  bool IsOpen();
  void Update(float dt);
  void Render();
  void Is(std::string type);
}
