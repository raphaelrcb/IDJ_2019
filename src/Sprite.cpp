#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/Game.hpp"
#include "../include/Sprite.hpp"
#include "../include/State.hpp"


Sprite::Sprite(){
  texture = nullptr;
}

Sprite::Sprite(std::string file){
  texture = nullptr;
  Open(file);
//  std::cout << "durante bg" << State::bg << std::endl;
}

Sprite::~Sprite(){
  std::cout << "\n chamando o destrutor na hora errada otário\n" << '\n';
  SDL_DestroyTexture(texture);
  // std::cout << "destrutor vazio" << '\n';
}

void Sprite::Open(std::string file){
  // Game& game = Game::GetInstance();//instâcnia local para o singleto
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  const char* path = file.c_str();
  texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);

  if (texture == nullptr){
      std::cout << "Error loading texture, Error code: "<< SDL_GetError() << std::endl;
  }
  else {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  }
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(int x, int y){
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = GetWidth();
  dstrect.h = GetHeight();
  int RenderError;
  //Game& game = Game::GetInstance();//instâcnia local para o singleto
  //SDL_Renderer* renderer = game.GetRenderer();

  RenderError = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
  if (RenderError != 0) {
    std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
  }
}

int Sprite::GetWidth(){
  return width;
}
int Sprite::GetHeight(){
  return height;
}

bool Sprite::IsOpen(){
  if (texture == nullptr) {
    return false;
  }
  else {
    return true;
  }
}
