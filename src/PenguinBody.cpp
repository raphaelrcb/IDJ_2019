#include "../include/PenguinBody.hpp"

PenguinBody::PenguinBody(GameObject& associated)
                                                :Component(associated){

  speed = Vec2();//inicialiizando as variáveis
  linearSpeed = 0;
  angle = 0;
  hp = (std::rand() % 100) + 1000;

  std::shared_ptr<Sprite> penguinb_sprite(new Sprite(associated, PENGUINBODY_PATH));
  associated.AddComponent(penguinb_sprite);//cirando a sprite e adicionando ao vetor de components

  std::shared_ptr<Collider> penguinb_collider(new Collider(associated));//criando a sprite e adicionando ao vetor de Components
  associated.AddComponent(penguinb_collider);

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

  InputManager& input = InputManager::GetInstance();

  if (input.IsKeyDown(A_KEY)) {
    std::cout << "A" << '\n';
    angle -= PENGUIN_ANGULAR_SPEED*dt;

  }
  if (input.IsKeyDown(D_KEY)) {
     std::cout << "D" << '\n';
     angle += PENGUIN_ANGULAR_SPEED*dt;
  }

  associated.angleDeg = angle;

  if (input.IsKeyDown(W_KEY) && (linearSpeed <= PENGUIN_MAX_SPEED)) {//é definido uma velocidade máxima à qual a câmera pode acelerar
    std::cout << "W" << '\n';
    linearSpeed+=PENGUIN_DELTA_SPEED*dt;

  }
   else if (input.IsKeyDown(S_KEY) && (linearSpeed >= PENGUIN_MIN_SPEED)) {
     std::cout << "S" << '\n';
     linearSpeed-=PENGUIN_DELTA_SPEED*dt;

  } else {

    if (linearSpeed > 0){//com essa lógica a movimentação nao para instantâneamente, mas a velocidade diminui gradativamente até 0
      linearSpeed -= PENGUIN_DELTA_SPEED*dt/FRICTION;

    }
    else if (linearSpeed < 0){
      linearSpeed += PENGUIN_DELTA_SPEED*dt/FRICTION;

    }
    else{
      speed = Vec2();
    }
  }

  speed.x = linearSpeed;
  speed.y = 0;

  speed.Rotate(-angle*PI/180);
  associated.box.x += speed.x*dt;
  associated.box.y += speed.y*dt;



  if (hp <= 0) {
    hp = 0;
    associated.RequestDelete();
  }
}

void PenguinBody::Render(){


}

bool PenguinBody::Is(std::string type){
  return (type == "PenguinBody");
}
