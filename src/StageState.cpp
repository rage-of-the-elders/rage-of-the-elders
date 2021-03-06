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
#include "Teacher.h"
#include "Boss.h"
#include "VictoryState.h"
#include "GameOverState.h"
#include "CameraBarrier.h"
#include "LifeItem.h"
#include "SceneObject.h"

#include <iostream>

int StageState::enemiesCount = 0;

StageState::StageState() : music("audio/stage-1/bg.ogg") {
  this->quitRequested = false;
  this->hordeEnabled = false;
  this->started = false;
	this->objectArray = std::vector<std::shared_ptr<GameObject>>();
  this->arrowTimer = Timer();
  this->arrowDurationTimer = Timer();
  this->arrowDurationTimer.Set(3);
  this->arrowGO = new GameObject();
  GameObject *go = new GameObject();
  this->goSound = new Sound(*go, "audio/go.ogg");
}

StageState::~StageState() {
  UnlockCamera();
  Camera::position = Vec2();
  StageState::enemiesCount = 0;
  this->objectArray.clear();
}

void StageState::LoadAssets() {
  this->LoadBackground();
  this->LoadGates();
  this->LoadPlayers();
	this->BuildBarriers();
  this->LoadSceneObjects();
	this->music.Play();
}

void StageState::LoadSceneObjects() {
  this->objectMap = new ObjectMap("positioning_furniture1.txt", this->stageLimit, 30, 90);
  for(auto &sceneObject : this->objectMap->GetObjectList()) {
    GameObject *sceneObjectGO = new GameObject();
    this->objectMap->At(sceneObject.x, sceneObject.y) = sceneObject.objectType;
    Vec2 objectPosition = this->objectMap->GetObjectPosition(sceneObject.x, sceneObject.y);
    SceneObject *newSceneObject = new SceneObject(*sceneObjectGO, sceneObject.environment,
                                      objectPosition.x, objectPosition.y, sceneObject.objectType);
    sceneObjectGO->AddComponent(newSceneObject);
    this->AddObject(sceneObjectGO);

    GameObject *sceneObjectBarrierGO = new GameObject();
    sceneObjectBarrierGO->AddComponent(new Barrier(*sceneObjectBarrierGO, newSceneObject->GetColisionRect()));
    this->AddObject(sceneObjectBarrierGO);
  }
}

void StageState::LoadBackground() {
  this->bg = new GameObject();
	this->bg->AddComponent(new Sprite(*(this->bg), "img/black.png"));
	this->bg->box = Rect();

	GameObject *tileMapGO = new GameObject();
	this->tileSet = new TileSet(570, 560, 720, "img/stage1v4-paralax.png");
	this->tileMap = new TileMap(*tileMapGO, "map/tilesStage1.txt", tileSet);
	tileMapGO->AddComponent(tileMap);
	tileMapGO->box = Rect();

  bg->AddComponent(new CameraFollower(*bg));

  this->stageLimit = tileMap->MapEnd();
  Camera::finalCameraLimit = this->stageLimit;
}

void StageState::LoadPlayers() {
  GameObject *playerGO = new GameObject();
  playerGO->box.SetCenterPos(600, 300);

  if (GameData::choosedCharacter == "veteran") {
    playerGO->AddComponent(new Veteran(*playerGO));
  } else {
    playerGO->AddComponent(new Teacher(*playerGO));
  }
  this->AddObject(playerGO);
  Camera::Follow(playerGO);

  GameObject *nurseGO = new GameObject();
  nurseGO->box.SetCenterPos(800, 500);
  nurseGO->AddComponent(new Nurse(*nurseGO));
  this->AddObject(nurseGO);
  nurseGO->RequestDelete();

  GameObject *bossGO = new GameObject();
  bossGO->box.SetCenterPos(800, 500);
  bossGO->AddComponent(new Boss(*bossGO));
  this->AddObject(bossGO);
  bossGO->RequestDelete();
  
  GameObject *janitorGO = new GameObject();
  janitorGO->box.SetCenterPos(800, 500);
  janitorGO->AddComponent(new Janitor(*janitorGO));
  this->AddObject(janitorGO);
  janitorGO->RequestDelete();
  
  
  GameObject *securityGO = new GameObject();
  securityGO->box.SetCenterPos(800, 500);
  securityGO->AddComponent(new Security(*securityGO));
  this->AddObject(securityGO);
  securityGO->RequestDelete();
}

void StageState::BuildBarriers() {
  GameObject *hallWall = new GameObject();
  hallWall->AddComponent(new Barrier(*hallWall, Rect(0, 0, this->tileMap->GetTileEnd(17), 555)));
  this->AddObject(hallWall);

  GameObject *roomWall = new GameObject();
  roomWall->AddComponent(new Barrier(*roomWall, Rect(0, 0, this->stageLimit , 420)));
  this->AddObject(roomWall);

  GameObject *baseFloor = new GameObject();
  baseFloor->AddComponent(new Barrier(*baseFloor, Rect(0,720,this->stageLimit,400)));
  this->AddObject(baseFloor);

  GameObject *initialWall = new GameObject();
  initialWall->AddComponent(new Barrier(*initialWall, Rect(0, 0, 335, 1420)));
  this->AddObject(initialWall);

  GameObject *finalWall = new GameObject();
  finalWall->AddComponent(new Barrier(*finalWall, Rect(this->stageLimit, -400, 400, 1420)));
  this->AddObject(finalWall);
}

void StageState::LoadGates() {
  this->gateMap = new GateMap("map/hordesStage3.txt");
}

void StageState::Update(float dt) {
	this->quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}
  if (InputManager::GetInstance().IsKeyDown(O_KEY)) {
    this->popRequested = true;
    Game::GetInstance().Push(new VictoryState());
  }
  if (InputManager::GetInstance().IsKeyDown(I_KEY)) {
    this->popRequested = true;
    Game::GetInstance().Push(new GameOverState());
  }

  this->HandleHorde();

	Camera::Update(dt);
	this->bg->Update(dt);
	this->tileMap->Update(dt);

	this->UpdateArray(dt);
	this->CollisionCheck();
	this->DeletionCheck();
	this->CheckGameEnd();
  this->arrowDurationTimer.Update(dt);
  if (arrowDurationTimer.Get() < 3) {
    this->arrowTimer.Update(dt);
    if (arrowTimer.Get() > 0.5) {
      this->arrowGO->ToggleActive();
      arrowTimer.Restart();
      this->goSound->Play(1);
    }
  } else {
    if (arrowGO->IsActive())
      arrowGO->Desactivate();
  }
}

void StageState::HandleHorde() {
  #ifdef DEBUG
    if (InputManager::GetInstance().KeyPress(P_KEY)) {
      this->UnlockCamera();
    }
  #endif

  if (this->hordeEnabled and (StageState::enemiesCount <= 0)) {
    this->UnlockCamera();
    this->arrowGO = new GameObject();
    arrowGO->AddComponent(new Sprite(*arrowGO, "img/go_arrow.png"));
    arrowGO->AddComponent(new CameraFollower(*arrowGO, {1000, 100}));
    this->AddObject(arrowGO);
    arrowDurationTimer.Restart();
  }

  Gate currentGate = this->gateMap->GetCurrentGate();

  if(currentGate.position > 0) {
    int gatePosition = this->tileMap->GetTileEnd(currentGate.position);
    if (Playable::player != nullptr) {
      int playerPosition = Camera::position.x;
      if(playerPosition >= gatePosition && playerPosition <= (gatePosition + Game::screenWidth)) {
        this->LockCamera(gatePosition);
        this->SpawnEnemies(gatePosition, currentGate);
        this->hordeEnabled = true;
      }
    }
  }
}

void StageState::LockCamera(int gatePosition) {
    Camera::initiaCameraLimit = gatePosition;
    Camera::finalCameraLimit = gatePosition + Game::screenWidth;
    this->gateMap->NextGate();

    this->cameraLockWallLeft = new GameObject();
    cameraLockWallLeft->AddComponent(new CameraBarrier(*cameraLockWallLeft, CameraBarrier::LEFT_SIDE, Rect(Camera::initiaCameraLimit, Camera::position.y, -10, 900)));
    this->AddObject(cameraLockWallLeft);

    this->cameraLockWallRight = new GameObject();
    cameraLockWallRight->AddComponent(new CameraBarrier(*cameraLockWallRight, CameraBarrier::RIGHT_SIDE, Rect(Camera::finalCameraLimit, Camera::position.y, 10, 900)));
    this->AddObject(cameraLockWallRight);
}

void StageState::UnlockCamera() {
  if (this->hordeEnabled) {
    Camera::initiaCameraLimit = 0;
    Camera::finalCameraLimit = this->stageLimit;

    if (this->cameraLockWallLeft) {
      this->cameraLockWallLeft->RequestDelete();
    }
    if (this->cameraLockWallRight) {
      this->cameraLockWallRight->RequestDelete();
    }
    this->hordeEnabled = false;
  }


  // if(this->arrowTimer.Get() > 2) {
  //   arrowGO->Activate();
  //   this->arrowTimer.Restart();
  // }
  // else {
  //   arrowGO->Desactivate();
  // }
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
    case 4:
      enemyGO->AddComponent(new Boss(*enemyGO));
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
  StageState::enemiesCount++;
}

void StageState::SpawnEnemies(int gatePosition, Gate gate) {
  for (int i = 0; i < gate.enemiesAmount; i++) {
    Spawn(gatePosition, gate.enemies[i].type, gate.enemies[i].invertSide);
  }
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
  return GameData::playerVictory;
}

bool StageState::PlayerLose() {
  return Playable::player == nullptr;
}

void StageState::CheckGameEnd() {
	if (this->PlayerWon()) {
		GameData::playerVictory = true;
		this->popRequested = true;
		Game::GetInstance().Push(new VictoryState());
	}
	else if (this->PlayerLose()) {
		GameData::playerVictory = false;
		this->popRequested = true;
		Game::GetInstance().Push(new GameOverState());
	}
}

#include<iostream>

void StageState::CollisionCheck() {
	for (unsigned i = 0; i < this->objectArray.size(); i++) {
		for (unsigned j = i + 1; j < this->objectArray.size(); j++) {
      if(objectArray[i]->IsActive() && objectArray[j]->IsActive()) {
        if(objectArray[i]->Has("Fighter") && objectArray[j]->Has("Fighter")){
            std::vector<std::shared_ptr<Component>> cptsA = objectArray[i]->GetAllComponent("Collider");
            std::vector<std::shared_ptr<Component>> cptsB = objectArray[j]->GetAllComponent("Collider");

            // cptsA[0].get();

            // for(auto &cpt : objsA) {
              // Collider *objA = (Collider *) ;
            // }
            // puts("AAAAAAAAAAAAAAAA");



            // for(auto &cpt : objectArray[i]->GetAllComponent("Collider")) {
            Collider *objA = (Collider *) cptsA[0].get();
            Collider *objB = (Collider *) cptsA[1].get();
            Collider *objC = (Collider *) cptsB[0].get();
            Collider *objD = (Collider *) cptsB[1].get();
              // for(auto &cpt2 : objectArray[j]->GetAllComponent("Collider")) {
              // }
            // }
            // std::cout << objA->GetColliderType() << " " << objB->GetColliderType() << " " << objC->GetColliderType() << " " << objD->GetColliderType() << std::endl;

            if(Collision::IsColliding(objA->box, objC->box, 0, 0) && (objA->GetColliderType() != objC->GetColliderType())) {
                this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
                this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
            }
            if(Collision::IsColliding(objA->box, objD->box, 0, 0) && (objA->GetColliderType() != objD->GetColliderType())) {
                this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
                this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
            }
            if(Collision::IsColliding(objC->box, objB->box, 0, 0) && (objC->GetColliderType() != objB->GetColliderType())) {
                this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
                this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
            }
            if(Collision::IsColliding(objD->box, objB->box, 0, 0) && (objD->GetColliderType() != objB->GetColliderType())) {
                this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
                this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
            }
            // Collision::IsColliding(objA->box, objB->box, this->objectArray[i]->angleDeg, this->objectArray[j]->angleDeg
            // if(objA && objB) {
            //   if (Collision::IsColliding(objA->box, objB->box, this->objectArray[i]->angleDeg, this->objectArray[j]->angleDeg)) {
            //     this->objectArray[i]->NotifyCollision(*(this->objectArray[j]));
            //     this->objectArray[j]->NotifyCollision(*(this->objectArray[i]));
            //   }
            // }
        }
        else {
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
}

void StageState::DeletionCheck() {
	for (int i = objectArray.size() - 1; i >= 0; i--)
		if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
		}
}

void StageState::DecreaseEnemiesCount() {
  StageState::enemiesCount--;
}

void StageState::Pause() {}
void StageState::Resume() {}
