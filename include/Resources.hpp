#pragma once

#include <string.h>
#include <unordered_map>
#include "Game.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "Sound.hpp"

class Game;
class Resources{

  private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;

  public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();

    static Mix_Music* GetMusic(std::string file);
    static void ClearMusics();

    static Mix_Chunk* GetSound(std::string file);
    static void ClearSounds();

};
// + public
// - private
// # protected
// _ static
