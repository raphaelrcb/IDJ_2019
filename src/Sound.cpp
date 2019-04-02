#include "Sound.hpp"

#define empty_channel -1 //

Sound::Sound(GameObject& associated):Component(associated){
  Component::associated = associated;
  chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file):Sound::Sound(associated){
  Open(file);
}

Sound::~Sound(){
  if (chunk != nullptr) {
    Mix_HaltChannel(int channel);
  }
  Mix_FreeChunk(chunk)
}

void Sound::Play(){
  if (chunk != nullptr) {
  channel = Mix_PlayChannel(empty_channel, chunk, times -1);//empty_channel = -1 a função escolherá o primeiro canal vazio e retornará o número dele
  // loops indica quantas vezes o som deve ser repetido, ou seja, loops = 1 faz tocar duas vezes.
  } else {
    std::cout << "Chunk null, can't play sound" << std::endl;
  }
}

void Sound::Stop(){
  if (chunk != nullptr) {
    Mix_HaltChannel(int channel);
  } else {
    std::cout << "Chunk null, no sound to stop" << std::endl;
  }
}

void Sound::Open(std::string file){
  Mix_Chunk* LoadError =  Mix_LoadWAV(file);
  if (LoadError == nullptr) {
    std::cout << "Error loadind sound" << std::endl;
  }
}

bool Sound::IsOpen(){
}

void Sound::Update(float dt){
}

void Sound::Render(){
}

void Is(std::string type){
  if (type == "Sound") {
    return true;
  } else {
    return false;
  }
}
