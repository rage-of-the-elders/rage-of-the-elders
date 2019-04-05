#include "State.h"
#include "Vec2.h"

State::State() : music("audio/stageState.ogg") {
  this->quitRequested = false;
  this->music.Play();

	GameObject *bg = new GameObject();
	Component *bgSprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(bgSprite);
	objectArray.emplace_back(bg);

	srand(time(NULL));
}

State::~State() {
  this->objectArray.clear();
}
void State::LoadAssets() {
  // TODO
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			this->quitRequested = true;
		}
		
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			// Traveling the array backwards to always click on the object from above
			for (int i = objectArray.size() - 1; i >= 0; i--) {
				GameObject* go = (GameObject*) objectArray[i].get();

        if (go->box.Contains( (float)mouseX, (float)mouseY ) ) {
					Face* face = (Face*)go->GetComponent("Face");
					if (face != nullptr) {
						face->Damage(std::rand() % 10 + 10);
            break; // Exits the loop to hit only one face
          }
				}
			}
		}

		if (event.type == SDL_KEYDOWN) {
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			} else {
				// FIXME
				// cstdlib, ctime
				// Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				// AddObject((int)objPos.x, (int)objPos.y);
				this->AddObject(mouseX, mouseY);
			}
		}
	}
}

void State::Update(float dt) {
  this->Input();

  for (auto &gameObj : this->objectArray)
    gameObj->Update(dt);

  for (int i = objectArray.size() - 1; i >= 0; i--)
    if (objectArray[i]->IsDead())
      objectArray.erase(objectArray.begin() + i);
}

void State::Render() {
  for (auto &gameObj : this->objectArray)
		gameObj->Render();
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject *gameObj = new GameObject();
	gameObj->box.x = mouseX;
	gameObj->box.y = mouseY;

	Sprite *sprite = new Sprite(*gameObj, "img/penguinface.png");
	Sound *sound = new Sound(*gameObj, "audio/boom.wav");
	Face *face = new Face(*gameObj);

	gameObj->AddComponent(sprite);
	gameObj->AddComponent(sound);
	gameObj->AddComponent(face);

	this->objectArray.emplace_back(gameObj);
}

bool State::QuitRequested() {
  return quitRequested;
}