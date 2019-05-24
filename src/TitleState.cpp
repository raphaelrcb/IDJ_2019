#include "../include/TitleState.hpp"
#include "../include/Game.hpp"

TitleState::TitleState(){

  GameObject *title_object = new GameObject();

  std::weak_ptr<GameObject> weak_title = AddObject(title_object);
  std::shared_ptr<GameObject> title = weak_title.lock();

  title->box.x = 0;
  title->box.y = 0;

  std::shared_ptr<Sprite> title_sprite(new Sprite(*title, TITLE_PATH));
  std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*title));

  title->AddComponent(title_sprite);
  title->AddComponent(CamFollow);

  GameObject *text_object = new GameObject();

  std::weak_ptr<GameObject> weak_text = AddObject(text_object);
  std::shared_ptr<GameObject> text = weak_text.lock();

  std::shared_ptr<Text> title_text(new Text(*text, FONT_PATH, FONT_SIZE, Text::BLENDED, TITLE_TEXT, TEXT_COLOR, {0, 0, 0, 0}));
  text->box.x = 512 - text->box.w/2;
  text->box.y = 512 - text->box.h/2;
  text->AddComponent(title_text);
}

TitleState::~TitleState(){
  objectArray.clear();
}


void TitleState::LoadAssets(){

}

void TitleState::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  Game& game = Game::GetInstance();

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (input.KeyPress(SPACE_KEY)) {
    StageState* stageState = new StageState();
    game.Push(stageState);
  }

  UpdateArray(dt);
}

void TitleState::Render(){
  RenderArray();
}


void TitleState::Start(){
  LoadAssets();
  StartArray();
  started = true;
}

void TitleState::Pause(){

}

void TitleState::Resume(){
}
