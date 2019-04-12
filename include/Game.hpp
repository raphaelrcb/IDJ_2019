#pragma once

#include <SDL2/SDL.h>
#include <SDL_include.h>
#include "State.hpp"
#include "Resources.hpp"

class State;
class Resources;
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
