#include <iostream>
#include <SDL2/SDL.h>
#include "State.hpp"

State::State():bg("assets/img/ocean.jpg"),
  music("assets/audio/stageState.ogg"){
  // bg = Sprite("assets/img/ocean.jpg");
  quitRequested = false;//inicializa o quitRequested
  // LoadAssets();//carrega as imagens e músicasa serem utilizadas
  music.Play(-1);//toca a música carregada
}

void State::LoadAssets(){

  // Sprite* aux_bg =  new Sprite("assets/img/ocean.jpg");
  // bg = *(aux_bg);
  // Music* aux_music = new Music("assets/audio/stageState.ogg");
  // music = *(aux_music);

  bg = Sprite("assets/img/ocean.jpg");
  music = Music("assets/audio/stageState.ogg");

}

void State::Update(float dt){
  quitRequested = SDL_QuitRequested();
}

void State::Render(){
  bg.Render(0,0);//renderiza na posição 0,0 da tela (canto esquerdo superior)
}
bool State::QuitRequested(){
    return quitRequested;
}
