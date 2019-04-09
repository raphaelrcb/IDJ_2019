#include <SDL2/SDL.h>
#include <string.h>

class TileSet{

private:

  Sprite tileSet;
  int rows;
  int columns;
  int tileWidth;
  int tileHeight;

public:

  TileSet(int tileWidth, int tileHeight, std::string file);

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();

}
