#include "../include/InputManager.hpp"


// InputManager *InputManager::instance = nullptr;
InputManager::InputManager(){//inicializando todas a as variáveis

  for (int i = 0; i < 6; i++) {
    mouseUpdate[i] = 0;
  }
  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;

}

InputManager::~InputManager(){
}


void InputManager::Update(){
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
