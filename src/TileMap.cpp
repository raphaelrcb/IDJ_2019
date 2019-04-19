#include "../include/TileMap.hpp"

#include "Camera.hpp"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet):Component(associated){

  if (tileSet != nullptr) {
    SetTileSet(tileSet);
    Load(file);
  } else {
    std::cout << "tileSet null" << std::endl;
  }

}

void TileMap::Load(std::string file){
  std::fstream map;
  map.open(file);
  int tile;

  map >> mapWidth;
  map.seekg (1, map.cur);
  map >> mapHeight;
  map.seekg (1, map.cur);
  map >> mapDepth;
  map.seekg (1, map.cur);
  // std::cout << mapWidth <<" " << mapHeight <<" " <<mapDepth << '\n';

  for (int i = 0; i < (mapWidth*mapHeight*mapDepth); i++){
    map >> tile;
    tileMatrix.push_back(tile-1);
    map.seekg (1, map.cur);
    // std::cout << tile <<tileMatrix[i] << '\n';
  }
  // std::cout <<  mapWidth << " " << mapHeight << " " <<  mapDepth  << '\n';
  map.close();

}

void TileMap::SetTileSet(TileSet* tileSet){
  this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z = 0){//x é coluna, y é linha e z é profundidade
  //o cálculo é feito por linha + (tamanho da linha)*coluna + (área do tilemap)*profundidade
  return (tileMatrix[x + mapWidth*y + mapWidth*mapHeight*z]);
}

void TileMap::Render(){
  for (int z = 0; z < mapDepth; z++) {
    RenderLayer(z, this->associated.box.x + Camera::pos.x, this->associated.box.y + Camera::pos.y);
    // associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y
  }
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){

  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {

      // std::cout << At(j, i, layer) << ":" << '\n';
      tileSet->RenderTile(At(j, i, layer), cameraX + tileSet->GetTileWidth()*j , cameraY + tileSet->GetTileHeight()*i);

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
