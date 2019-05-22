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
#include "Game.h"
#include "TitleState.h"
#include "EndState.h"
#include "GameData.h"

StageState::StageState() : music("audio/stageState.ogg") {
  this->quitRequested = false;
  this->started = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();
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

	for(int i = 0; i < 3; i++) {
		GameObject* go = new GameObject();
		go->AddComponent(new Alien(*go, (int) Math::GetRand(4, 8), Math::GetRand(1, 5)));
		go->box.SetCenterPos(rand()%1024, rand()%600);
		AddObject(go);
	}

	GameObject *penguinGO = new GameObject();
	penguinGO->AddComponent(new PenguinBody(*penguinGO));
	penguinGO->box.SetCenterPos(704, 640);
	this->AddObject(penguinGO);

	Camera::Follow(penguinGO);

	this->music.Play();
}

void StageState::Update(float dt) {
	this->quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}

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
	this->CheckGameEnd();
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

bool StageState::PlayerWon() {
	return Alien::alienCount <= 0;
}

bool StageState::PlayerLose() {
	return PenguinBody::player == nullptr;
}

void StageState::CheckGameEnd() {
	if (this->PlayerWon()) {
		GameData::playerVictory = true;
		Game::GetInstance().Push(new EndState());
		this->popRequested = true;
	}
	else if (this->PlayerLose()) {
		GameData::playerVictory = false;
		Game::GetInstance().Push(new EndState());
		this->popRequested = true;
	}
}

	void StageState::Pause() {}
	void StageState::Resume() {}