#include "State.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

State::State() : music("audio/stageState.ogg") {
  this->quitRequested = false;
  this->started = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();

	GameObject *alienGO = new GameObject();
	alienGO->AddComponent(new Alien(*alienGO, 8));
	alienGO->box.SetPos(512 - alienGO->box.w / 2, 300 - alienGO->box.h / 2);
	AddObject(alienGO);

	this->music.Play();
	srand(time(NULL));
}

State::~State() {
  this->objectArray.clear();
}

void State::LoadAssets() {
	this->bg = new GameObject();
	this->bg->AddComponent(new Sprite(*(this->bg), "img/ocean.jpg"));
	this->bg->box = Rect();

	this->mapGameObj = new GameObject();
	TileSet *tileSet = new TileSet(*mapGameObj, 64, 64, "img/tileset.png");
	TileMap *tileMap = new TileMap(*mapGameObj, "map/tileMap.txt", tileSet);
	mapGameObj->AddComponent(tileMap);
	mapGameObj->box = Rect();

	bg->AddComponent(new CameraFollower(*bg));
}

void State::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

	Camera::Update(dt);
	this->bg->Update(dt);
	this->mapGameObj->Update(dt);

	// if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
	// 	Vec2 objPos = Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())
	// 									.Rotate(200, rand() % 360);
	// 	this->AddObject((int)objPos.x, (int)objPos.y);
	// }

  for (auto &gameObj : this->objectArray)
    gameObj->Update(dt);

  for (int i = objectArray.size() - 1; i >= 0; i--)
    if (objectArray[i]->IsDead()) {
			Camera::Unfollow();
      objectArray.erase(objectArray.begin() + i);
		}
}

void State::Render() {
	this->bg->Render();
	this->mapGameObj->GetComponent("TileMap")->Render();

	for (auto &gameObj : this->objectArray)
		gameObj->Render();
}

// void State::AddObject(int mouseX, int mouseY) {
// 	GameObject *gameObj = new GameObject();

// 	Sprite *sprite = new Sprite(*gameObj, "img/penguinface.png");
// 	Sound *sound = new Sound(*gameObj, "audio/boom.wav");
// 	Face *face = new Face(*gameObj);

// 	gameObj->AddComponent(sprite);
// 	gameObj->AddComponent(sound);
// 	gameObj->AddComponent(face);

// 	this->objectArray.emplace_back(gameObj);
// 	gameObj->box = Rect((mouseX - sprite->GetWidth() / 2),
// 											(mouseY - sprite->GetHeight() / 2),
// 											sprite->GetWidth(),
// 											sprite->GetHeight());
// }

bool State::QuitRequested() {
  return quitRequested;
}

void State::Start() {
	this->LoadAssets();

	for (auto &obj : this->objectArray)
		obj->Start();

	this->started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
	std::shared_ptr<GameObject> ptr = std::shared_ptr<GameObject>(go);
	objectArray.push_back(ptr);

	if (started)
		ptr->Start();
	return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
	for (auto &obj : objectArray) {
		if (obj.get() == go) {
			std::weak_ptr<GameObject> weakPtr = obj;
			return weakPtr;
		}
	}
	return std::weak_ptr<GameObject>();
}
