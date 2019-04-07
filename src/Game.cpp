#include <iostream>
#include <string>
#include "../include/Game.hpp"

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
    std::cout << "SDL initiated" << std::endl;
    ImgError = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG |IMG_INIT_TIF);//img_init carregar os loaders da imagem, e retorna um bitmask correspondente aos loaders que ela conseguiu carregar
    if (ImgError == 0) {//se não carrefar nenhum, o retorno é 0 e há um erro
      std::cout << "IMIG_Init failed to load" << std::endl;
    }
    else {//conseguindo iniciar as imagens, inicializa-se a música, que funciona de forma semelhante à imagem.
      std::cout << "Image initiated" << std::endl;
      MixError = Mix_Init( MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG); //mix_init carregar os loaders das músicas, e retorna um bitmask correspondente aos loaders que ela conseguiu carregar
      if (MixError == 0){//se não carregar nenhum loadoer, o retorno é 0 e há um erro
        std::cout << "MIX_Init failed to load" << std::endl;
      }
      else{//channels é a quantidade de canais de saída de áudio (default = 2), formtat é o formato da amostra baseado no suporte de audio do SDL, Frequency é a frequência do som, e chuncksize são os bytes usados por amostra
        std::cout << "Mix initiated" << std::endl;
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_CHUNKSIZE);
        Mix_AllocateChannels(AUDIO_CHANNELS);//aloca os canais de áudio usados pelo jogo

        const char* Window_title = title.c_str();//converte o valor dado em string para cons char*
        SDL_Window* window = SDL_CreateWindow(Window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);//cria a janela em que o jogo vai ser executado
        if (window == nullptr) {//as entradas de create wndow passam o nome da janela, a posição dela na tela (a flag centraliza), tamanho da tela (width e height) e uma flag para padrões da janela
        std::cout << "Failed to create window, error code: " << SDL_GetError() << std::endl;
        }
        else {
          std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//cria um renderizador para a janela cirada, como entradas colocamos a janela, um valor de index que determinaqual dos drivers devemos usar;
        //o valor -1 faz o SDL escolher o melhor renderizador para o ambiente e para as flags setadas, o terceiro argumento é a flag
        if (window == nullptr) {
          std::cout << "Failed to create render, error code: " << SDL_GetError() << std::endl;
        }
        else{
          std::cout << "Renderer created" << std::endl;
        }
      }
    }
  }
  state = new State();//instancia um novo estado
  srand(time(NULL));

}

Game& Game::GetInstance(){//cria a instância do jogo
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

Game::~Game(){//destrutor desfaz as inicializações, deleta o estado, ecerra SDL_Music e SDL_image, destrói o renderizador e a janela e encerra a SDL
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State& Game::GetState(){//Retorna o estado atual
  return *state;
}

SDL_Renderer* Game::GetRenderer(){//Retorna o renderer a ser usado
  return renderer;
}

void Game::Run(){//loop principal do jogo, será implementado em 4 etapas, porém nesse trabalho apenas as etapas 3 e 4
  do{
    state->Update(0);//etapa 3
    state->Render();//etapa 4
    SDL_RenderPresent(Game::GetInstance().GetRenderer());
    SDL_Delay(33);//impõe-se um limite de framerate, com um delay de 33ms, nos dará aproximadamente 30 FPS, (usado para não usar 100% di cpu já que é desnecessário)
  } while(state->QuitRequested() != true);
}
