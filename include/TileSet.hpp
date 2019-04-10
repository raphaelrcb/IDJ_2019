#include <string.h>
#include "Sprite.hpp"


class TileSet{

private:

  Sprite *tileSet;//verificar lista de inicialização 

  int rows;
  int columns;
  int tileWidth;
  int tileHeight;

public:
  TileSet();
  ~TileSet();
  TileSet(int tileW, int tileH, std::string file);
  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();

};
