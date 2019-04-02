#include "../include/State.hpp"

State::State():bg("assets/img/ocean.jpg"),//o construtor é iniciado já instamnciando bg e music, assim não é necessário usar LoadAssets ainda
  music("assets/audio/stageState.ogg"){

  quitRequested = false;//inicializa o quitRequested
  // LoadAssets();//carrega as imagens e músicasa serem utilizadas
  music.Play(-1);//toca a música carregada
}

void State::LoadAssets(){//não é chamada pelo State
  // Sprite* aux_bg =  new Sprite("assets/img/ocean.jpg");
  // bg = *(aux_bg);
  // Music* aux_music = new Music("assets/audio/stageState.ogg");
  // music = *(aux_music);
  bg = Sprite("assets/img/ocean.jpg");
  music = Music("assets/audio/stageState.ogg");

}

void State::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo
  quitRequested = SDL_QuitRequested();
}

void State::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  bg.Render(/*0,0 PASSAR BOX PRA CÁ*/);//renderiza na posição 0,0 da tela (canto esquerdo superior)
}
bool State::QuitRequested(){
    return quitRequested;//retorna o nome da flag usada para encerrar o gjogo
}
