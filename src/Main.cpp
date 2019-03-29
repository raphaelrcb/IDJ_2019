#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../include/Game.hpp"
#include "../include/State.hpp"
#include "../include/Sprite.hpp"
#include "../include/Music.hpp"

int main(int argc, char const *argv[]) {
  Game& game = Game::GetInstance();
  game.Run();
  game.~Game();
  return 0;
}
