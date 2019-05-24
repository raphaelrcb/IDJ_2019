#include "../include/StageState.hpp"
#include "../include/Game.hpp"
#include "../include/GameData.hpp"



StageState::StageState(){


  /////////////////Background
  GameObject *bg_object = new GameObject();

  std::weak_ptr<GameObject> weak_bg =  AddObject(bg_object);
  std::shared_ptr<GameObject> bg = weak_bg.lock();

  bg->box.x = 0;
  bg->box.y = 0;
  std::shared_ptr<Sprite> bg_sprite(new Sprite(*bg, BG_PATH));
  std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*bg));
  bg->AddComponent(bg_sprite);
  bg->AddComponent(CamFollow);

  ////////////////TileSet
  // std::shared_ptr<GameObject> tileObject = std::shared_ptr<GameObject> (new GameObject());
  GameObject *tile_object = new GameObject();

  std::weak_ptr<GameObject> weak_tile = AddObject(tile_object);
  std::shared_ptr<GameObject> tileObject = weak_tile.lock();

  tileObject->box.x = 0;
  tileObject->box.y = 0;
  TileSet* tileSet(new TileSet(*tileObject, 64, 64, TILESET_PATH));
  std::shared_ptr<TileMap> tileMap(new TileMap(*tileObject, TILEMAP_PATH , tileSet));

  tileObject->AddComponent(tileMap);

  ////////////////ALIENS
  float nAliens = 2 + ( (rand() % 3) );

  // int nAliens = 3;
  for (int i = 0; i < nAliens; i++) {
    /* code */
    GameObject *alien_object = new GameObject();

    std::weak_ptr<GameObject> weak_alien =  AddObject(alien_object);
    std::shared_ptr<GameObject> alien = weak_alien.lock();
    std::shared_ptr<Alien> alien_s(new Alien(*alien, N_MINIONS, i*0.9));

    alien->box.x = 512 - (1+15*i)*alien->box.w/2;
    alien->box.y = 300 - (1-15*i)*alien->box.h/2;
    alien->AddComponent(alien_s);
  }

  ////////////////PENGUIN
  GameObject *penguin_object = new GameObject();

  std::weak_ptr<GameObject> weak_penguin =  AddObject(penguin_object);
  std::shared_ptr<GameObject> penguin = weak_penguin.lock();
  std::shared_ptr<PenguinBody> penguin_s(new PenguinBody(*penguin));

  penguin->box.x = 704;
  penguin->box.y = 640;
  penguin->AddComponent(penguin_s);
  Camera::Follow(penguin.get());



  quitRequested = false;//inicializa o quitRequested
  started = false;
  // LoadAssets();//carrega as imagens e músicasa serem utilizadas
  backgroundMusic.Open(MUSIC_PATH);
  backgroundMusic.Play(-1);//toca a música carregada
}

void StageState::LoadAssets(){

  // bg.Open("assets/img/ocean.jpg");
  // backgroundMusic.Open(MUSIC_PATH);

}

void StageState::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo

  InputManager& input = InputManager::GetInstance();
  Game& game = Game::GetInstance();
  Camera::Update(dt);

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    popRequested = true;
  }

  // std::cout<< "n objects = " << objectArray.size() << '\n';

  if (Alien::alienCount == 0) {//se o pinguin derrotou todos os aliens, ele foi vitorioso e salvou o mundo
    popRequested = true;
    GameData::playerVictory = true;
    EndState* endState = new EndState();
    game.Push(endState);
  }
  else if (PenguinBody::player == nullptr && Alien::alienCount > 0) {//se o pinguin morreu e sobraram aliens, ele foi derrotado e o mundo está condenada
    popRequested = true;
    GameData::playerVictory = false;
    EndState* endState = new EndState();
    game.Push(endState);
  }

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin()+i);
    }
  }

  UpdateArray(dt);

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    std::shared_ptr<Component> collider_update = objectArray[i]->GetComponent("Collider");
    if (collider_update != nullptr) {//atulliza os colliders de cada objeto
      (std::dynamic_pointer_cast<Collider>(collider_update))->Update(dt);//atualiza os colisores para não ficarem "atrás" do objeto
    }
  }

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    // std::shared_ptr<Component> cpt_a = objectArray[i]->GetComponent("Collider");
    std::shared_ptr<Collider> cpt_a = std::dynamic_pointer_cast<Collider>(objectArray[i]->GetComponent("Collider"));
    if (cpt_a != nullptr) {

      for (unsigned int j = i + 1; j < objectArray.size(); j++) {
        // std::shared_ptr<Component> cpt_b = objectArray[j]->GetComponent("Collider");
        std::shared_ptr<Collider> cpt_b = std::dynamic_pointer_cast<Collider>(objectArray[j]->GetComponent("Collider"));

        if (cpt_b != nullptr) {

          if (Collision::IsColliding( cpt_a->box, cpt_b->box, objectArray[i]->angleDeg,  objectArray[j]->angleDeg)) {
            objectArray[i]->NotifyCollision( *objectArray[j] );
            objectArray[j]->NotifyCollision( *objectArray[i] );
          }
        }
      }
    }
  }

}

void StageState::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  RenderArray();
}

// bool StageState::QuitRequested(){
//     return quitRequested;//retorna o nome da flag usada para encerrar o gjogo
// }

StageState::~StageState(){
  objectArray.clear();
}

// std::weak_ptr<GameObject> StageState::AddObject(GameObject* go){
//
//   std::shared_ptr<GameObject> shared(go);
//   objectArray.emplace_back(shared);//adicionando o shared object criado no object array
//
//   std::weak_ptr<GameObject> weak;
//   weak = objectArray.back();//weak recebe o último elemento adicionado no object array (que é o shared criado)
//
//   if (started) {
//     objectArray.back()->Start();
//   }
//
//   return weak;
// }

// std::weak_ptr<GameObject> StageState::GetObjectPtr(GameObject* go){
//
//   std::weak_ptr<GameObject> weak;
//   for (unsigned int i = 0; i < objectArray.size(); i++) {
//     if (objectArray[i].get() == go) {
//       weak = objectArray[i];
//       return weak;
//     }
//   }
//   return weak ;
// }

void StageState::Start(){
  LoadAssets();
  StartArray();
  started = true;
}

void StageState::Pause(){

}

void StageState::Resume(){

}
