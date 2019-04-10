#include "State.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"

State::State() : music("audio/stageState.ogg") {
  this->quitRequested = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();

	LoadAssets();

  this->music.Play();
	srand(time(NULL));
}

State::~State() {
  this->objectArray.clear();
}

void State::LoadAssets() {
	GameObject *bg = new GameObject();
	Component *bgSprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(bgSprite);
	this->objectArray.emplace_back(bg);

	GameObject *mapGameObj = new GameObject();
	TileSet *tileSet = new TileSet(*mapGameObj, 64, 64, "img/tileset.png");
	Component *tileMap = new TileMap(*mapGameObj, "map/tileMap.txt", tileSet);
	mapGameObj->AddComponent(tileMap);
	mapGameObj->box = Rect();
	this->objectArray.emplace_back(mapGameObj);
}

void State::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

	if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())
										.Rotate(200, rand() % 360);
		this->AddObject((int)objPos.x, (int)objPos.y);
	}

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

	Sprite *sprite = new Sprite(*gameObj, "img/penguinface.png");
	Sound *sound = new Sound(*gameObj, "audio/boom.wav");
	Face *face = new Face(*gameObj);

	gameObj->AddComponent(sprite);
	gameObj->AddComponent(sound);
	gameObj->AddComponent(face);

	this->objectArray.emplace_back(gameObj);
	gameObj->box = Rect(mouseX - sprite->GetWidth() / 2, mouseY - sprite->GetHeight() / 2,
									    sprite->GetWidth(), sprite->GetHeight());
}

bool State::QuitRequested() {
  return quitRequested;
}
