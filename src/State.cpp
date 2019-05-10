#include "../include/State.hpp"
#include "../include/CameraFollower.hpp"
#include "../include/Alien.hpp"


State::State(){


  /////////////////Background
  // std::shared_ptr<GameObject> bg = std::shared_ptr<GameObject> (new GameObject());
  GameObject *bg_object = new GameObject();

  std::weak_ptr<GameObject> weak_bg =  AddObject(bg_object);
  std::shared_ptr<GameObject> bg = weak_bg.lock();

  bg->box.x = 0;
  bg->box.y = 0;
  std::shared_ptr<Sprite> bg_sprite(new Sprite(*bg, BG_PATH));
  std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*bg));
  bg->AddComponent(bg_sprite);
  bg->AddComponent(CamFollow);
  // objectArray.emplace_back(std::move(bg));

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
  // objectArray.emplace_back(std::move(tileObject));

  ////////////////ALIEN
  GameObject *alien_object = new GameObject();

  std::weak_ptr<GameObject> weak_alien =  AddObject(alien_object);
  std::shared_ptr<GameObject> alien = weak_alien.lock();
  // alien->box.w = ALIEN_WIDTH;
  // alien->box.h =ALIEN_HEIGHT;
  std::shared_ptr<Alien> alien_s(new Alien(*alien, N_MINIONS));

  alien->box.x = 512 - alien->box.w/2;
  alien->box.y = 300 - alien->box.h/2;
  alien->AddComponent(alien_s);

  quitRequested = false;//inicializa o quitRequested
  started = false;
  // LoadAssets();//carrega as imagens e músicasa serem utilizadas
  music.Open(MUSIC_PATH);
  music.Play(-1);//toca a música carregada
}

void State::LoadAssets(){

  // bg.Open("assets/img/ocean.jpg");
  // music.Open(MUSIC_PATH);

}

void State::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo

  InputManager& input = InputManager::GetInstance();
  Camera::Update(dt);

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (input.KeyPress(SPACE_KEY)){
    // std::cout << " space tleck" << '\n';
    Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( input.GetMouseX(), input.GetMouseY() );
    // AddObject((int)objPos.x, (int)objPos.y);
  }

  for (int i = objectArray.size() - 1; i >= 0; --i) {
      objectArray[i]->Update(dt);
  }

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin()+i);
    }
  }
}

void State::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Render();
  }
}

bool State::QuitRequested(){
    return quitRequested;//retorna o nome da flag usada para encerrar o gjogo
}

State::~State(){
  objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){

  std::shared_ptr<GameObject> shared(go);
  objectArray.push_back(shared);//adicionando o shared object criado no object array

  std::weak_ptr<GameObject> weak;
  weak = objectArray.back();//weak recebe o último elemento adicionado no object array (que é o shared criado)

  if (started) {
    objectArray.back()->Start();
  }

  return weak;
}

/////////////////////////////FACE
  // std::shared_ptr<GameObject> enemy = std::shared_ptr<GameObject> (new GameObject());//instancia um GameObject para o que vai ser colocado no vetor ObjectArray com os componentes do inimigo
  //
  // std::shared_ptr<Sprite> enemy_sprite(new Sprite(*enemy, ENEMY_SPRITE_PATH));
  // std::shared_ptr<Sound> enemy_sound(new Sound(*enemy, ENEMY_SOUND_PATH));
  // std::shared_ptr<Face> enemy_face(new Face(*enemy));
  //
  // enemy->box.x = mouseX - enemy_sprite->GetWidth()/2 + Camera::pos.x;
  // enemy->box.y = mouseY - enemy_sprite->GetHeight()/2 + Camera::pos.y;
  // enemy->box.w = enemy_sprite->GetWidth();
  // enemy->box.h = enemy_sprite->GetHeight();
  //
  // enemy->AddComponent(enemy_sprite);
  // enemy->AddComponent(enemy_sound);
  // enemy->AddComponent(enemy_face);

  // objectArray.emplace_back(std::move(enemy));
//////////////////////////////////

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){

  std::weak_ptr<GameObject> weak;
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i].get() == go) {
      weak = objectArray[i];
      return weak;
    }
  }
  return weak ;
}

void State::Start(){
  LoadAssets();
  std::cout << "start" << '\n';
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Start();
  }
  started = true;
}
