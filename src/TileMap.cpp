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
  std::fstream map;
  map.open("../assets/tileMap.txt");
  int tile;

  map >> mapWidth;
  map.seekg (1, map.cur);
  map >> mapHeight;
  map.seekg (1, map.cur);
  map >> mapDepth;

  for (int i = 0; i < (mapWidth*mapHeight*mapDepth); i++){
    map >> tile;
    tileMatrix.push_back(tile-1);
    map.seekg (1, map.cur);
  }

  map.close();
}

void TileMap::SetTileSet(TileSet* tileSet){
  this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){//x é coluna, y é linha e z é profundidade
  //o cálculo é feito por linha + (tamanho da linha)*coluna + (área do tilemap)*profundidade
  return tileMatrix[x + mapWidth*y + mapWidth*mapHeight*z];
}

void TileMap::Render(){
  for (int z = 0; z < mapDepth; z++) {
    RenderLayer(z, associated.box.x, associated.box.y);
  }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){

  for (int i = 0; i < mapHeight; i++) {
    for (int j = 0; j < mapWidth; j++) {
      tileSet->RenderTile(tileMatrix[layer*mapHeight*mapWidth + mapHeight*i + j], cameraX + tileSet->GetTileWidth()*j , cameraY + tileSet->GetTileHeight()*i);
    }
  }
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

bool TileMap::Is(std::string type){
  if (type == "TileMap") {
    return true;
  } else {
    return false;
  }
}

void TileMap::Update(float dt){
}
