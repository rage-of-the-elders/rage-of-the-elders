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

// int StageState::stageLimit = 0;

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

	GameObject *tileMapGO = new GameObject();
	this->tileSet = new TileSet(570, 560, 720, "img/stage1.png");
	this->tileMap = new TileMap(*tileMapGO, "map/stage1v2.txt", tileSet);
  this->stageLimit = tileMap->MapEnd();
	tileMapGO->AddComponent(tileMap);
	tileMapGO->box = Rect();

	bg->AddComponent(new CameraFollower(*bg));

	GameObject *veteranGO = new GameObject();
	veteranGO->box.SetCenterPos(600, 300);
	veteranGO->AddComponent(new Veteran(*veteranGO));
	this->AddObject(veteranGO);

	GameObject *nurseGO = new GameObject();
	nurseGO->AddComponent(new Nurse(*nurseGO));
	nurseGO->box.SetCenterPos(900, 450);
	this->AddObject(nurseGO);

	// FIXME
	GameObject *hallWall = new GameObject();
	hallWall->AddComponent(new Barrier(*hallWall, Rect(0, 0, this->tileMap->GetTileEnd(14), 555)));
	this->AddObject(hallWall);

  GameObject *roomWall = new GameObject();
	roomWall->AddComponent(new Barrier(*roomWall, Rect(0, 0, 12220, 420)));
	this->AddObject(roomWall);

  GameObject *baseFloor = new GameObject();
  baseFloor->AddComponent(new Barrier(*baseFloor, Rect(0,720,12220,400)));
  this->AddObject(baseFloor);

  GameObject *initialWall = new GameObject();
	initialWall->AddComponent(new Barrier(*initialWall, Rect(0, 0, 335, 1420)));
	this->AddObject(initialWall);

  GameObject *finalWall = new GameObject();
  finalWall->AddComponent(new Barrier(*finalWall, Rect(this->stageLimit, -400, 400, 1420)));
  this->AddObject(finalWall);

	Camera::Follow(veteranGO);

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
	this->tileMap->Update(dt);

	this->UpdateArray(dt);
	this->CollisionCheck();
	this->DeletionCheck();
	this->CheckGameEnd();
}

void StageState::Render() {
	this->bg->Render();
	this->tileMap->Render();

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

void StageState::CollisionCheck() {
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
