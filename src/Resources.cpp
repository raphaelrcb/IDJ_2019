#include "../include/Resources.hpp"
#include <iostream>
// #include "Game.hpp"

// Inicializa as variáveis estáticas da classe
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = {{"", nullptr}};
std::unordered_map<std::string, Mix_Music*> Resources::musicTable = {{"", nullptr}};
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = {{"", nullptr}};


SDL_Texture* Resources::GetImage(std::string file){

     std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.find(file);//procura o arquivo solicitado na tabela de imagens

     if ( it == imageTable.end() ){//Caso não encontre a imagem, abre e aloca ela na memória

       const char* path = file.c_str();
       SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);

       if (texture == nullptr){
           std::cout << "Error loading texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
       } else {
         imageTable.emplace (file, texture);//coloca a imagem e seu caminho na tabela
         return texture;
       }

     }
       return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
       // std::cout << it->first << " is " << it->second;
}


 void Resources::ClearImages(){
   std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.begin();

   while (it != imageTable.end()) {//para todos as imagens na tabela, desaloca a memória e apaga da tabela
     SDL_DestroyTexture(it->second);
     it = imageTable.erase(it);
   }
   imageTable.clear();//limpa a tabela
   // std::cout << "cleared" << '\n';
 }


 Mix_Music* Resources::GetMusic(std::string file){

   std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.find(file);//procura o arquivo solicitado na tabela de Músicas

   if ( it == musicTable.end() ){//Caso não encontre a música, abre e aloca ela na memória

     const char* path = file.c_str();
     Mix_Music* music = Mix_LoadMUS(path);

     if (music == nullptr){
         std::cout << "Error loading music, Error code: "<< SDL_GetError() << std::endl;
     } else {
       musicTable.emplace (file, music);//coloca a música e seu caminho na tabela
       return music;
     }

   }
     return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
     // std::cout << it->first << " is " << it->second;
 }

 void Resources::ClearMusics(){

   std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.begin();

   while (it != musicTable.end()) {//para todos as musicas na tabela, desaloca a memória e apaga da tabela
     Mix_FreeMusic(it->second);
     it = musicTable.erase(it);
   }
   musicTable.clear();//limpa a tabela
   // std::cout << "cleared" << '\n';
 }


 Mix_Chunk* Resources::GetSound(std::string file){// Funciona de forma semelhante à GetImage e GetMusic
   std::unordered_map<std::string, Mix_Chunk*>::const_iterator it = soundTable.find(file);

   if ( it == soundTable.end() ){

     const char* path = file.c_str();
     Mix_Chunk* chunk = Mix_LoadWAV(path);

     if (chunk == nullptr){
         std::cout << "Error loading chunk, Error code: "<< SDL_GetError() << std::endl;
     } else {
       soundTable.emplace (file, chunk);
       return chunk;
     }

   }
     return (it->second);
     // std::cout << it->first << " is " << it->second;
 }

 void Resources::ClearSounds(){// Funciona de forma semelhante à ClearImages e ClearMusics
   std::unordered_map<std::string, Mix_Chunk*>::const_iterator it = soundTable.begin();

   while (it != soundTable.end()) {
     Mix_FreeChunk(it->second);
     it = soundTable.erase(it);
   }
   soundTable.clear();
   // std::cout << "cleared" << '\n';
 }
