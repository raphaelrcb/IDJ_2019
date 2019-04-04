#include "../include/State.hpp"
#define PI 3.14159265359

State::State() /*:    bg("assets/img/ocean.jpg"),//o construtor é iniciado já instamnciando bg e music, assim não é necessário usar LoadAssets ainda
  music("assets/audio/stageState.ogg")*/{

  GameObject *bg = new GameObject();
  // Sprite* enemy_sprite = new Sprite("img/penguinface.png");
  Sprite* bg_sprite;
  bg_sprite->Open("assets/img/ocean.jpg");
  bg->AddComponent(bg_sprite);

  quitRequested = false;//inicializa o quitRequested
  LoadAssets();//carrega as imagens e músicasa serem utilizadas
  music.Play(-1);//toca a música carregada
}

void State::LoadAssets(){

  // bg.Open("assets/img/ocean.jpg");
  music.Open("assets/audio/stageState.ogg");

}

void State::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo
  // quitRequested = SDL_QuitRequested();
  State::Input();
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead() == true) {
      objectArray.erase(objectArray.begin()+i);
    }
  }
}

void State::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  // bg.Render(/*0,0 PASSAR BOX PRA CÁ*/);//renderiza na posição 0,0 da tela (canto esquerdo superior)
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY){
  GameObject *enemy = new GameObject();
  // Sprite* enemy_sprite = new Sprite("img/penguinface.png");

  Sprite* enemy_sprite;
  enemy_sprite->Open("img/penguinface.png");

  enemy->AddComponent(enemy_sprite);
  enemy->box.x = (mouseX + enemy_sprite->GetWidth())/2 ;
  enemy->box.y = (mouseY + enemy_sprite->GetHeight())/2;
  enemy->box.w = enemy_sprite->GetWidth();
  enemy->box.h = enemy_sprite->GetHeight();

  // Sound* enemy_sound = new Sound(enemy, "audio/boom.wav");
  Sound* enemy_sound;
  enemy_sound->Open("audio/boom.wav");
  enemy->AddComponent(enemy_sound);

  // Face* enemy_face = new Face(enemy);
  Face* enemy_face;
  enemy->AddComponent(enemy_face);

  objectArray.emplace_back( enemy);
}
