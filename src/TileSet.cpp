#include "../include/TileSet.hpp"
// #include "../include/Sprite.hpp"
// TileSet::TileSet():tileSet{
// }

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){ //classe que constrói o tileSet

  this->tileWidth = tileWidth;//seta a largura do tile com a passada para a função
  this->tileHeight = tileHeight;//seta a largura do tile com a passada para a função
  tileSet->Open(file);//Abre o tileset
  rows = tileSet->GetWidth()/tileWidth;
  columns = tileSet->GetHeight()/tileHeight;
  //calcula o número de linhas colunas do tileset sado o tamnho dado pela função sprite

}/////////////////////////lista de inicialização?

void TileSet::RenderTile(unsigned index, float x, float y){

  if(  (index <= (unsigned)(columns*rows -1)) ){
    tileSet->SetClip((index/rows)*tileWidth, (index/(columns+1))*tileHeight, tileWidth, tileHeight);//verificar conta
    tileSet->Render(x, y);
  }
  std::cout << "index not valid" << std::endl;
}

int TileSet::GetTileWidth(){
  return tileWidth;
}

int TileSet::GetTileHeight(){
  return tileHeight;
}

TileSet::~TileSet(){

}
