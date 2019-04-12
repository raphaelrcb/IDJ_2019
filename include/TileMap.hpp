#include "TileSet.hpp"
#include <fstream>
#include <stdio.h>


class TileMap: public Component{

  private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;

  public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);

    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z);
    void Render();
    void RenderLayer(int layer, int cameraX, int cameraY);
    int GetWidth();
    int GetHeight();
    int GetDepth();
    bool Is(std::string type);
    void Update(float dt);
};
