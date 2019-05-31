#include "StageState.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Collision.h"
#include "Collider.h"
#include "Game.h"
#include "TitleState.h"
#include "EndState.h"
#include "GameData.h"
#include "Veteran.h"
#include "Nurse.h"
#include "Barrier.h"

#include<iostream>

StageState::StageState() : music("audio/stage1.ogg") {
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

	GameObject *veteranGO = new GameObject();
	veteranGO->box.SetCenterPos(600, 640);
	veteranGO->AddComponent(new Veteran(*veteranGO));
	this->AddObject(veteranGO);

	GameObject *nurseGO = new GameObject();
	nurseGO->AddComponent(new Nurse(*nurseGO));
	nurseGO->box.SetCenterPos(900, 640);
	this->AddObject(nurseGO);

	GameObject *wall = new GameObject();
	wall->AddComponent(new Barrier(*wall, Rect(300,400,1000,40)));
	
	this->AddObject(wall);

	Camera::Follow(veteranGO);

	// this->music.Play();
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
	this->CollisionCheck();
	this->DeletionCheck();
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
	return false;
}

bool StageState::PlayerLose() {
	return false;
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

#include<iostream>

void StageState::CollisionCheck() { // FIXME: Check isActive
	for (unsigned i = 0; i < this->objectArray.size(); i++) {
		for (unsigned j = i + 1; j < this->objectArray.size(); j++) {
			if (objectArray[i]->IsActive() && objectArray[j]->IsActive()) {
				Collider *objA = (Collider *)objectArray[i]->GetComponent("Collider");
				Collider *objB = (Collider *)objectArray[j]->GetComponent("Collider");

				if(objA && objB) {
					if (Collision::IsColliding(objA->box, objB->box, this->objectArray[i]->angleDeg, this->objectArray[j]->angleDeg)) {
						this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
						this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
					}
				}
			}
		}
	}
}
void StageState::DeletionCheck() {
	for (int i = objectArray.size() - 1; i >= 0; i--)
		if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
		}
}

void StageState::Pause() {}
void StageState::Resume() {}