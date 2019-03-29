#include "../include/Game.hpp"

int main(int argc, char const *argv[]) {

  Game& game = Game::GetInstance();//cria o game
  game.Run();//executa o game até a janela ser fechada
  game.~Game();//desaloca a memória, destrói as janelas, etc
  return 0;

}
