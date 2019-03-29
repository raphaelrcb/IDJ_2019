#pragma once

#include <SDL2/SDL.h>
#include <SDL_include.h>
#include "State.hpp"

class Game{

  private:
    Game (std::string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

  public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};
//SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
