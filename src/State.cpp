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
	alienGO->box.SetCenterPos(512, 300);
	this->AddObject(alienGO);

	this->music.Play();
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
