#include "Teacher.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "Game.h"
#include "Enemy.h"
#include "Nurse.h"
#include "Janitor.h"
#include "Security.h"
#include "Boss.h"

Teacher::Teacher(GameObject &associated) : Playable(associated) {
  this->hp = TEACHER_HP;
  this->speed = TEACHER_SPEED;
  this->player = this;
  this->orientation = RIGHT;
  this->damage[BASIC_ATTACK_TWO] = 10;
  this->damage[COMBO] = 7;
  this->ultimateDuration = Timer();
  this->enemys = std::vector <std::shared_ptr<GameObject>>();
  this->rightOfsetColliderAttack = -75;
  this->leftOfsetColliderAttack = 75;
  this->attackColliderGapBasicAtacck1 = 80;
  this->attackColliderGapBasicAtacck2 = 115;

  std::string character = "teacher";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/basic_attack_one.png", 21, 0.04, 0, false);
  this->sprite[BASIC_ATTACK_TWO] = new Sprite(this->associated, "img/" + character + "/basic_attack_two.png", 20, 0.04, 0, false);
  this->sprite[COMBO] = new Sprite(this->associated, "img/" + character + "/combo.png", 20, 0.04, 0, false);
  this->sprite[ULTIMATE_BEGIN] = new Sprite(this->associated, "img/" + character + "/ultimate_begin.png", 29, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 11, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 18, 0.04, 0, false);

  this->ActivateSprite(IDLE);


  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_TWO]);
  this->associated.AddComponent(this->sprite[COMBO]);
  this->associated.AddComponent(this->sprite[ULTIMATE_BEGIN]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);

  this->bodyColliderBox = new Collider(this->associated, {0.37,0.55});
  this->attackColliderBox = new Collider(this->associated, {0.3,0.55}, 1);
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->attackColliderBox->SetColliderType(1);
  this->sound[ULTIMATE_BEGIN] = new Sound(this->associated, "audio/teacher/ultimate.ogg");
}

Teacher::~Teacher() {
  Teacher::player = nullptr;
}

#include <iostream>

void Teacher::Update(float dt) {
  Playable::Update(dt);

  this->ultimateDuration.Update(dt);
  this->bodyColliderBox->SetOffset({this->orientation == LEFT ? 23 : -23,0});

  // std::cout << this->ultimateDuration.Get() << std::endl;
  if(this->enemys.size() > 0 && this->ultimateDuration.Get() > 5) {
    for(auto &enemy : this->enemys) {
      Enemy *enemyType = (Enemy *) enemy->GetComponent("Enemy");
      enemyType->SetState(IDLE);

      if(enemy->Has("Nurse")) {
        Nurse *nurseType = (Nurse *) enemy->GetComponent("Nurse");
        nurseType->ResetSpeed();
      }
      else if(enemy->Has("Janitor")) {
        Janitor *janitorType = (Janitor *) enemy->GetComponent("Janitor");
        janitorType->ResetSpeed();
      }
      else if(enemy->Has("Security")) {
        Security *securityType = (Security *) enemy->GetComponent("Security");
        securityType->ResetSpeed();
      }
      else if(enemy->Has("Boss")) {
        Boss *bossType = (Boss *) enemy->GetComponent("Boss");
        bossType->ResetSpeed();
      }
    }
    this->enemys.clear();
  }
  else if(this->ultimateDuration.Get() < 5) {
    for(auto &enemy : this->enemys) {
      Enemy *enemyType = (Enemy *) enemy->GetComponent("Enemy");
      enemyType->SetState(FROZEN);
    }
  }
}

void Teacher::HandleUltimateBegin(float dt) {
  if(not this->sprite[ULTIMATE_BEGIN]->IsActive()) {
    this->ActivateSprite(ULTIMATE_BEGIN);
    GameObject *ultimate = new GameObject();
    ultimate->box.SetCenterPos(this->GetBox().GetCenter() - Vec2(60, 365));
    auto sprite = new Sprite(*ultimate, "img/teacher/ultimate.png", 16, 0.04, 0.9, false);
    // auto sprite = new Sprite(*ultimate, "img/teacher/ultimate2.png", 16, 0.04, 0.9, true);
    sprite->SetScaleX(0.8);
    ultimate->AddComponent(sprite);
    Game::GetInstance().GetCurrentState().AddObject(ultimate);
    this->sound[ULTIMATE_BEGIN]->Play(1);
    // this->ultimateDuration.Restart();
  }
  if(this->sprite[ULTIMATE_BEGIN]->IsFinished()) {
    this->currentState = IDLE;
    this->sprite[ULTIMATE_BEGIN]->SetFrame(0);
    this->sprite[ULTIMATE_BEGIN]->SetFinished(false);
  } 

  std::vector <std::shared_ptr<GameObject>> objects = Game::GetInstance().GetCurrentState().GetObjects();

  for(auto &object : objects) {
    if(object->Has("Enemy")){
      this->enemys.push_back(object);
    }
  }

  for(auto &enemy : this->enemys) {
    Enemy *enemyType = (Enemy *) enemy->GetComponent("Enemy");
    enemyType->SetSpeed(0);
    enemyType->SetState(FROZEN);
  }

  this->ultimateDuration.Restart();

}

bool Teacher::Is(std::string type) {
  return (type == "Teacher" || Playable::Is(type));
}

float Teacher::GetHPPercentage() {
  return (this->hp*1.0/TEACHER_HP*1.0) * 100;
}