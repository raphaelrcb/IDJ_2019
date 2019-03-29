#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../include/Game.hpp"
#include "../include/State.hpp"

#define MIX_DEFAULT_FREQUENCY 22050
#define MIX_DEFAUTL_CHANNELS 2
#define MIX_CHUNKSIZE 1024
#define AUDIO_CHANNELS 32

//inicialização de membro estático da classe
Game *Game::instance = nullptr;

Game::Game (std::string title, int width, int height){

  int SDLError, ImgError, MixError;

  if (Game::instance != nullptr){//chechando se já existe uma instância do jogo rodando, se tiver existe um problema na lógica
    std::cout << "Game Logic Problem" << std::endl;
  }
  else{
    Game::instance = this;//se não houver uma instância do jogo rodando, recebe this
  }


  SDLError = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);//SDL_INIT retorna diferente de zero quando falaha
  if (SDLError != 0){//caso falhe, deve-se abortar e mostrar uma mensagem de erro
    std::cout << "SDL_Init failed, Error Code: " << SDL_GetError() << std::endl;//sdl_get error obtem o ultimo erro ocorrido na biblioteca
  }
  else {//casso não haja falha, inicia a imagem
    ImgError = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG |IMG_INIT_TIF);//img_init retorna um bitmask correspondente aos loaders que ela conseguiu carregar
    if (ImgError == 0) {//se não carrefar nenhum, o retorno é 0 e há um erro
      std::cout << "IMIG_Init failed to load" << std::endl;
    }
    else {//conseguindo iniciar as imagens, inicializa-se a música, que funciona de forma semelhante à imagem.
      MixError = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
      if (MixError == 0){
        std::cout << "MIX_Init failed to load" << std::endl;
      }
      else{
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, MIX_DEFAUTL_CHANNELS, MIX_CHUNKSIZE);
        Mix_AllocateChannels(AUDIO_CHANNELS);

        const char* Window_title = title.c_str();
        SDL_Window* window = SDL_CreateWindow(Window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (window == nullptr) {
        std::cout << "Failed to create window, error code: " << SDL_GetError() << std::endl;
        }
        else {
          std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (window == nullptr) {
          std::cout << "Failed to create render, error code: " << SDL_GetError() << std::endl;
        }
        else{
          std::cout << "Renderer created" << std::endl;
        }
      }
    }
  }
  state = new State();
}

Game& Game::GetInstance(){
  std::string title = "Raphael_R_C_Barbosa_14/0160281 ";
  int width = 1024;
  int height = 600;

  if(Game::instance != nullptr){
    return (*Game::instance);
  }
  else {
    Game::instance = new Game(title, width, height);
    return (*Game::instance);
  }
}

Game::~Game(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

State& Game::GetState(){
  return *state;
}

SDL_Renderer* Game::GetRenderer(){
  return renderer;
}

void Game::Run(){
  do{
    state->Update(0);
    state->Render();
    SDL_RenderPresent(Game::GetInstance().GetRenderer());
    SDL_Delay(33);
  } while(state->QuitRequested() != true);
}
