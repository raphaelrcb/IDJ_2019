#pragma once

#include <SDL2/SDL.h>
#include <SDL_include.h>
#include "State.hpp"
#include "Resources.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define MIX_CHUNKSIZE 1024
#define AUDIO_CHANNELS 32

class State;
class Resources;
class Game{

  private:
    Game (std::string title, int width, int height);

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    int frameStart;
    float dt;

    void CalculateDeltaTime();

  public:

    ~Game();

    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime();
};
