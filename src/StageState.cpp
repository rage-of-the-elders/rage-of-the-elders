#include "Vec2.h"
#include "Game.h"
#include "Nurse.h"
#include "Camera.h"
#include "Barrier.h"
#include "Veteran.h"
#include "TileMap.h"
#include "TileSet.h"
#include "EndState.h"
#include "GameData.h"
#include "Janitor.h"
#include "Security.h"
#include "Collider.h"
#include "Collision.h"
#include "MathHelper.h"
#include "TitleState.h"
#include "StageState.h"
#include "InputManager.h"
#include "CameraFollower.h"

StageState::StageState() : music("audio/stage1.ogg") {
  this->quitRequested = false;
  this->started = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();
}

StageState::~StageState() {
  this->objectArray.clear();
}

void StageState::LoadAssets() {
  this->LoadBackground();
  this->LoadGates();
  this->LoadPlayers();
	this->BuildBarriers();
	this->music.Play();
}

void StageState::LoadBackground() {
  this->bg = new GameObject();
	this->bg->AddComponent(new Sprite(*(this->bg), "img/ocean.jpg"));
	this->bg->box = Rect();

	GameObject *tileMapGO = new GameObject();
	this->tileSet = new TileSet(570, 560, 720, "img/stage1.png");
	this->tileMap = new TileMap(*tileMapGO, "map/tilesStage1.txt", tileSet);
	tileMapGO->AddComponent(tileMap);
	tileMapGO->box = Rect();

  bg->AddComponent(new CameraFollower(*bg));

  this->stageLimit = tileMap->MapEnd();
  Camera::finalCameraLimit = this->stageLimit;
}

void StageState::LoadPlayers() {
  GameObject *veteranGO = new GameObject();
  veteranGO->box.SetCenterPos(600, 300);
  veteranGO->AddComponent(new Veteran(*veteranGO));
  this->AddObject(veteranGO);

	Camera::Follow(veteranGO);
}

void StageState::BuildBarriers() {
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
}

void StageState::LoadGates() {
  this->gateMap = new GateMap("map/hordesStage1.txt");
}

void StageState::Update(float dt) {
	this->quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}

  this->HandleHorde();

	Camera::Update(dt);
	this->bg->Update(dt);
	this->tileMap->Update(dt);

	this->UpdateArray(dt);
	this->CollisionCheck();
	this->DeletionCheck();
	this->CheckGameEnd();
}

void StageState::HandleHorde() {
  if (InputManager::GetInstance().KeyPress(P_KEY)) {
    this->UnlockCamera();
  }

  if(this->gateMap->GetCurrentGate() > 0) {
    // TODO: Change "Veteran" class to "Player"
    int gatePosition = this->tileMap->GetTileEnd(this->gateMap->GetCurrentGate());
    if (Veteran::player != nullptr) {
      int playerPosition = Veteran::player->GetBox().GetCenter().x - (Game::screenWidth / 2);

      if(playerPosition >= gatePosition && playerPosition <= (gatePosition + Game::screenWidth)) {
        this->LockCamera(gatePosition);
        this->SpawnEnemies(gatePosition);
      }
    }
  }
}

void StageState::LockCamera(int gatePosition) {
    Camera::initiaCameraLimit = gatePosition;
    Camera::finalCameraLimit = gatePosition + Game::screenWidth;
    this->gateMap->NextGate();
}

void StageState::UnlockCamera() {
  Camera::initiaCameraLimit = 0;
  Camera::finalCameraLimit = this->stageLimit;
}

/*
  If you want the enemy to come from the left side of the screen, set the value
  of "invertSide" as zero. Otherwise, set the attribute to a non-zero value.

  yLimit defines the limit where a enemy can be rendered. Default is 500px
  (Usualy, this is near the base of the wall)
*/
void StageState::Spawn(int gate, int type, int invertSide, int yLimit) {
  GameObject *enemyGO = new GameObject();

  switch (type) {
    case 1:
      enemyGO->AddComponent(new Nurse(*enemyGO));
      break;
    case 2:
      enemyGO->AddComponent(new Janitor(*enemyGO));
      break;
    case 3:
      enemyGO->AddComponent(new Security(*enemyGO));
      break;
    default:
      printf("WARNING: No enemy type given!\n");
      delete enemyGO;
      return;
  }

  Vec2 enemySize = enemyGO->box.GetSize();

  int yPosition = CalculateEnemyY(enemySize, yLimit);

  if(invertSide)
    enemyGO->box.SetPos(gate + Game::screenWidth, std::min(yPosition, Game::screenHeight));
  else
    enemyGO->box.SetPos(gate - enemySize.x, std::min(yPosition, Game::screenHeight));

  this->AddObject(enemyGO);
}

void StageState::SpawnEnemies(int gatePosition) {
  Spawn(gatePosition, 1, 0);
  Spawn(gatePosition, 2, 1);
  Spawn(gatePosition, 3, 1);
}

int StageState::CalculateEnemyY(Vec2 enemySize, int yLimit) {
  return ((Game::screenHeight - yLimit) * Math::GetRand(0, 1))
          - enemySize.y
          + yLimit;
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
