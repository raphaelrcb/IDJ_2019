#include "../include/TileMap.hpp"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet):Component(associated){

  if (tileSet != nullptr) {
    Load(file);
    SetTileSet(tileSet);
  } else {
    std::cout << "tileSet null" << std::endl;
  }

}

void TileMap::Load(std::string file){
  std::ofstream map;
  map.open("../assets/tileMap.txt");
  // FILE *map = fopen("../assets/tileMap.txt", "r");
  // if (!map){
    // std::cout << "could not open file" << std::endl;
  // }

  //Criar lógica pra ler o filemap

  // if (!map)
    // fclose(map);

  map.close();
}

void TileMap::SetTileSet(TileSet* tileSet){
}

int& TileMap::At(int x, int y, int z){//x é coluna, y é linha e z é profundidade
  //o cálculo é feito por linha + (tamanho da linha)*coluna + (área do tilemap)*profundidade
  return tileMatrix[0/*x + (tileSet->rows)*y + (tileSet->rows*tileSet->columns)*z*/];
}

void TileMap::Render(){
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
}

int TileMap::GetWidth(){
  return mapWidth;
}

int TileMap::GetHeight(){
  return mapHeight;
}

int TileMap::GetDepth(){
  return mapDepth;
}
