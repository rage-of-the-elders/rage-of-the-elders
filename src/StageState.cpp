#include "StageState.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"

StageState::StageState() : music("audio/stageState.ogg") {
  this->quitRequested = false;
  this->started = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();

	GameObject *alienGO = new GameObject();
	alienGO->AddComponent(new Alien(*alienGO, 8));
	alienGO->box.SetCenterPos(512, 300);
	this->AddObject(alienGO);

	GameObject *penguinGO = new GameObject();
	penguinGO->AddComponent(new PenguinBody(*penguinGO));
	penguinGO->box.SetCenterPos(704, 640);
	this->AddObject(penguinGO);

	Camera::Follow(penguinGO);

	this->music.Play();
}

StageState::~StageState() {
  this->objectArray.clear();
}

void StageState::LoadAssets() {
	this->bg = new GameObject();
	this->bg->AddComponent(new Sprite(*(this->bg), "img/ocean.jpg"));
	this->bg->box = Rect();

	this->mapGameObj = new GameObject();
	this->tileSet = new TileSet(*mapGameObj, 64, 64, "img/tileset.png");
	TileMap *tileMap = new TileMap(*mapGameObj, "map/tileMap.txt", tileSet);
	mapGameObj->AddComponent(tileMap);
	mapGameObj->box = Rect();

	bg->AddComponent(new CameraFollower(*bg));
}

void StageState::Update(float dt) {
	this->quitRequested = InputManager::GetInstance().QuitRequested();

	Camera::Update(dt);
	this->bg->Update(dt);
	this->mapGameObj->Update(dt);

	this->UpdateArray(dt);

	for (unsigned i = 0; i < this->objectArray.size(); i++) // TODO: Move to function
		for (unsigned j = i + 1; j < this->objectArray.size(); j++) {
			Collider *objA = (Collider *)objectArray[i]->GetComponent("Collider");
			Collider *objB = (Collider *)objectArray[j]->GetComponent("Collider");

			if(objA && objB) {
				if (Collision::IsColliding(objA->box, objB->box, this->objectArray[i]->angleDeg, this->objectArray[j]->angleDeg)) {
					this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
					this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
				}
			}
		}

	for (int i = objectArray.size() - 1; i >= 0; i--) // TODO: Move to function
		if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
		}
}

void StageState::Render() {
	this->bg->Render();
	this->mapGameObj->GetComponent("TileMap")->Render();

	this->RenderArray();	
}

void StageState::Start() {
	this->LoadAssets();
	this->StartArray();
	this->started = true;
}

void StageState::Pause() {}
void StageState::Resume() {}