#include "../include/PenguinBody.hpp"

PenguinBody::PenguinBody(GameObject& associated)
                                                :Component(associated){

  speed = Vec2();//inicialiizando as variáveis
  linearSpeed = 0;
  angle = 0;
  hp = (std::rand() % 100) + 1000;

  std::shared_ptr<Sprite> penguinb_sprite(new Sprite(associated, PENGUINBODY_PATH));
  associated.AddComponent(penguinb_sprite);//cirando a sprite e adicionando ao vetor de components

  player = this;//seta a variável de instância(player) com a instância da classe criada para que seja acessado por outros lugares no código

}

PenguinBody::~PenguinBody(){
  player = nullptr;//seta a variável de instância como nullptr, para que outras entidades saibam que o objeto foi deletado.
}


void PenguinBody::Start(){

  GameObject *penguinc_object = new GameObject();
  pcannon =  Game::GetInstance().GetState().AddObject(penguinc_object);//pega a função AddObject do state para adicionar o novo bullet ao array de objetos
  std::shared_ptr<GameObject> penguin_cannon = pcannon.lock();

  penguin_cannon->box.x = associated.box.x;
  penguin_cannon->box.y = associated.box.y;

  std::weak_ptr<GameObject> weak_pbody = Game::GetInstance().GetState().GetObjectPtr(&associated);

  std::shared_ptr<PenguinCannon> penguin_c(new PenguinCannon(*penguin_cannon, weak_pbody));//divide o arco de 360 graus pela quantidade de bullets desejada para que tenham a mesma distância entre si
  penguin_cannon->AddComponent(penguin_c);
}

void PenguinBody::Update(float dt){


}

void PenguinBody::Render(){


}

bool PenguinBody::Is(std::string type){
  return (type == "PenguinBody");
}
