#pragma once

#include <unordered_map>
#include <string.h>
#include <memory>
#include "Game.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "Text.hpp"

class Game;
class Resources{

  private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> > soundTable;
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font> > fontTable;


  public:
    static std::shared_ptr<SDL_Texture> GetImage(std::string file);
    static void ClearImages();

    static std::shared_ptr<Mix_Music> GetMusic(std::string file);
    static void ClearMusics();

    static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
    static void ClearSounds();

    static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
    static void ClearFonts();

};
// TTF_Font* TTF_OpenFont (const char* file, int ptsize)
// void TTF_CloseFont (TTF_Font* font)
// TTF_CloseFont (TTF_Font* font)
