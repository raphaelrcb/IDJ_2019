#include "../include/Game.hpp"
#include "../include/Sprite.hpp"


Sprite::Sprite(){//seta texture como nullptr (imagem não carregada)
  texture = nullptr;
}

Sprite::Sprite(std::string file){//seta texture como nullptr e em seguida chama Open para abrir uma imagem
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite(){//destrutor, caso haja uma imagem alocada, desaloca
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

void Sprite::Open(std::string file){//carrega a imagem indicada pelo caminho file
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);//desaloca qualquer imagem alocada antes
  }

  const char* path = file.c_str();//converte o caminho de string para const char* como é o tipo utilizado pela função
  texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);//carrega a imagem

  if (texture == nullptr){
      std::cout << "Error loading texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
  }
  else {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);//obtém os parâmetros (dimensões) da imagem e armazena-os nos espaçços indicados nos argumentos
  }
  SetClip(0, 0, width, height);//seta o clip com as dimensões da imagem
}

void Sprite::SetClip(int x, int y, int w, int h){// seta o clip com os parâmetros sasos
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(int x, int y){// wrapper para a SDL_RenderCopy que possui quatro argumentos
  SDL_Rect dstrect;// um dos parâmetros de RenderCOpy, é o retâncgulo de destino, determina a posição da tela em que a textura será renderizada,
  // se a altura e largura forem diferentes da original, há uma mudança de escala da imagem
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = GetWidth();
  dstrect.h = GetHeight();
  int RenderError;
  //Game& game = Game::GetInstance();//instâcnia local para o singleto
  //SDL_Renderer* renderer = game.GetRenderer();

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
