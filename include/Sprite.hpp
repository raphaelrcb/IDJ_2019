#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_include.h>
#include "GameObject.hpp"

class Sprite: public Component{//implementar update, is e render da classe mãe (component)
  private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

  public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void  Render(GameObject& associated/*int x, int y*/);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetBox(GameObject& associated
    void Render();
    void Is(std::string type);
};
