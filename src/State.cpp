#include "../include/State.hpp"

State::State():bg("assets/img/ocean.jpg"),//o construtor é iniciado já instamnciando bg e music, assim não é necessário usar LoadAssets ainda
  music("assets/audio/stageState.ogg"){

  quitRequested = false;//inicializa o quitRequested
  // LoadAssets();//carrega as imagens e músicasa serem utilizadas
  music.Play(-1);//toca a música carregada
}

void State::LoadAssets(){//não é chamada pelo State
  // Sprite* aux_bg =  new Sprite("assets/img/ocean.jpg");
  // bg = *(aux_bg);
  // Music* aux_music = new Music("assets/audio/stageState.ogg");
  // music = *(aux_music);
  bg = Sprite("assets/img/ocean.jpg");
  music = Music("assets/audio/stageState.ogg");

}

void State::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo
  // quitRequested = SDL_QuitRequested();
}

void State::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  bg.Render(/*0,0 PASSAR BOX PRA CÁ*/);//renderiza na posição 0,0 da tela (canto esquerdo superior)
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

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
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
