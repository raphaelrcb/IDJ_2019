#include <string.h>
#include "Sprite.hpp"



class TileSet{

private:
  Sprite tileSet;

  int rows;
  int columns;
  int tileWidth;
  int tileHeight;

public:
  TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file);

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();

};
