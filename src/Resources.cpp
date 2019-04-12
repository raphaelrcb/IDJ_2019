#include "../include/Resources.hpp"
#include <iostream>
// #include "Game.hpp"

// Game *Game::instance = nullptr;
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = {{"", nullptr}};
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = {{"", nullptr}};
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = {{"", nullptr}};


SDL_Texture* Resources::GetImage(std::string file){

     std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.find(file);

     if ( it == imageTable.end() ){//abre a imagem

       const char* path = file.c_str();
       SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);

       if (texture == nullptr){
           std::cout << "Error loading texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
       } else {
         imageTable.emplace (file, texture);
         return texture;
       }

     }
       return (it->second);
       // std::cout << it->first << " is " << it->second;
}

 // for (size_t i = 0; i < imageTable.size(); i++) {
 //   imageTable.first == file? return *imageTable:;
 // }

 void Resources::ClearImages(){
   std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.begin();

   while (it != imageTable.end()) {
     SDL_DestroyTexture(it->second);
     it = imageTable.erase(it);
   }
   imageTable.clear();
   // std::cout << "cleared" << '\n';
 }


 Mix_Music* Resources::GetMusic(std::string file){

   std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.find(file);

   if ( it == musicTable.end() ){//abre a musicm

     const char* path = file.c_str();
     Mix_Music* music = Mix_LoadMUS(path);

     if (music == nullptr){
         std::cout << "Error loading music, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
     } else {
       musicTable.emplace (file, music);
       return music;
     }

   }
     return (it->second);
     // std::cout << it->first << " is " << it->second;


 }

 void Resources::ClearMusics(){

   std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.begin();

   // Music::Stop(0);
   while (it != musicTable.end()) {
     Mix_FreeMusic(it->second);
     it = musicTable.erase(it);
   }
   musicTable.clear();
   // std::cout << "cleared" << '\n';
 }


 Mix_Chunk* Resources::GetSound(std::string file){
   std::unordered_map<std::string, Mix_Chunk*>::const_iterator it = soundTable.find(file);

   if ( it == soundTable.end() ){//abre a soundm

     const char* path = file.c_str();
     Mix_Chunk* chunk = Mix_LoadWAV(path);

     if (chunk == nullptr){
         std::cout << "Error loading chunk, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
     } else {
       soundTable.emplace (file, chunk);
       return chunk;
     }

   }
     return (it->second);
     // std::cout << it->first << " is " << it->second;
   // return nullptr;
 }

 void Resources::ClearSounds(){
   std::unordered_map<std::string, Mix_Chunk*>::const_iterator it = soundTable.begin();

   // Music::Stop(0);
   while (it != soundTable.end()) {
     Mix_FreeChunk(it->second);
     it = soundTable.erase(it);
   }
   soundTable.clear();
   // std::cout << "cleared" << '\n';
 }
