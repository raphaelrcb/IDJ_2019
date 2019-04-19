#include "../include/InputManager.hpp"


// InputManager *InputManager::instance = nullptr;
InputManager::InputManager(){//inicializando todas a as variáveis

  for (int i = 0; i < 6; i++) {
    mouseUpdate[i] = 0;
    mouseState[i] = false;
  }
  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;

}

InputManager::~InputManager(){
}


void InputManager::Update(){
  SDL_Event event;
  // unsigned int keySize;
  // int mouseX,mouseY;

  // SDL_GetMouseState(&mouseX, mouseY);

  while (SDL_PollEvent(&event)) {

    switch (event.type) {

      case SDL_QUIT:// SDL_QUIT  Clique no X, Alt+F4, etc.
        quitRequested = true;
        break;

      case SDL_KEYDOWN:// SDL_KEYDOWN   Pressionamento de tecla
        keyState[event.key.keysym.sym] = true;
        keyUpdate[event.key.keysym.sym] = updateCounter;
        break;

      case  SDL_KEYUP:// SDL_KEYUP     Uma tecla foi solta
        keyState[event.key.keysym.sym] = false;
        break;

      case SDL_MOUSEBUTTONDOWN:// SDL_MOUSEBUTTONDOWN Pressionamento de botão do mouse
        mouseState[event.button.button] = true;
        mouseUpdate[event.button.button] +=1;
        break;

      case SDL_MOUSEBUTTONUP:// SDL_MOUSEBUTTONUP Botão do mouse foi solto
        mouseState[event.button.button] = true;
        mouseUpdate[event.button.button] -=1;
        break;


      default:
        break;
    }
/////////////////////
    // std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.find(file);//procura o arquivo solicitado na tabela de Músicas
    //
    // if ( it == musicTable.end() ){//Caso não encontre a música, abre e aloca ela na memória
    //
    //   if (music == nullptr){
    //       std::cout << "Error loading music, Error code: "<< SDL_GetError() << std::endl;
    //   } else {
    //     musicTable.emplace (file, music);//coloca a música e seu caminho na tabela
    //     return music;
    //   }
    //
    // }
    //   return (it->second);//caso encontre a imagem na tabela retorna seu ponteiro
    //   // std::cout << it->first << " is " << it->second;
  //}///////////////////////

    if (event.type == SDL_KEYUP){


    }

    if (event.type == SDL_MOUSEBUTTONUP){// SDL_MOUSEBUTTONUP Botão do mouse foi solto

      if (event.button.button == SDL_BUTTON_LEFT) {
        mouseState[0] = false;
      }
      if (event.button.button == SDL_BUTTON_MIDDLE) {
        mouseState[1] = false;
      }
      if (event.button.button == SDL_BUTTON_RIGHT) {
        mouseState[2] = false;
      }
      if (event.button.button == SDL_BUTTON_X1) {
        mouseState[3] = false;
      }
      if (event.button.button == SDL_BUTTON_X2) {
        mouseState[4] = false;
      }

    }
  }
}


bool InputManager::KeyPress(int key){
  return false;
}

bool InputManager::KeyRelease(int key){
  return false;
}

bool InputManager::IsKeyDown(int key){
  return false;
}


bool InputManager::MousePress(int key){
  return false;
}

bool InputManager::MouseRelease(int key){
  return false;
}

bool InputManager::IsMouseDown(int key){
  return false;
}


int InputManager::GetMouseX(){
  return 0;
}

int InputManager::GetMouseY(){
  return 0;
}


bool InputManager::QuitRequested(){
  return false;
}


InputManager& InputManager::GetInstance(){
  static InputManager input;
  return input;
}
