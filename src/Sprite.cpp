#include "../include/Game.hpp"
#include "../include/Sprite.hpp"
#include "../include/Camera.hpp"


Sprite::Sprite(GameObject& associated)
                                      :Component(associated){//seta texture como nullptr (imagem não carregada)
  texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file)
                                                        :Component(associated){//seta texture como nullptr e em seguida chama Open para abrir uma imagem
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){//carrega a imagem indicada pelo caminho file
  texture = Resources::GetImage(file);

  if (texture == nullptr){
      std::cout << "Error returning texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
  }
  else {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);//obtém os parâmetros (dimensões) da imagem e armazena-os nos espaçços indicados nos argumentos
  }
  SetClip(0, 0, width, height);//seta o clip com as dimensões da imagem

  associated.box.w = width;
  associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h){// seta o clip com os parâmetros sasos
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(){//chama o render utilizando o associated como argumento
  Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
  // Render(associated.box.x, associated.box.y);

}

void Sprite::Render(int x, int y){// wrapper para a SDL_RenderCopy que possui quatro argumentos
  SDL_Rect dstrect;// um dos parâmetros de RenderCOpy, é o retâncgulo de destino, determina a posição da tela em que a textura será renderizada,
  // se a altura e largura forem diferentes da original, há uma mudança de escala da imagem
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;
  int RenderError;

  RenderError = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
  if (RenderError != 0) {
    std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
  }
}



int Sprite::GetWidth(){//retorna a largura da imagem
  return width;
}
int Sprite::GetHeight(){//retorna a altura da imagem
  return height;
}

bool Sprite::IsOpen(){//verifica se a imagem foi aberta
  if (texture == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

bool Sprite::Is(std::string type){
  if (type == "Sprite") {
    return true;
  } else {
    return false;
  }
}

void Sprite::Update(float dt){
}
