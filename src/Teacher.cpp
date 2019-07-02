#include "Teacher.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "Game.h"
#include "Enemy.h"

Teacher::Teacher(GameObject &associated) : Playable(associated) {
  this->hp = TEACHER_HP;
  this->speed = TEACHER_SPEED;
  this->player = this;
  this->orientation = RIGHT;
  this->damage[BASIC_ATTACK_TWO] = 10;
  this->damage[COMBO] = 7;
  this->ultimateDuration = Timer();
  this->enemys = std::vector <std::shared_ptr<GameObject>>();

  std::string character = "teacher";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 30, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/basic_attack_one.png", 12, 0.04, 0, false);
  this->sprite[BASIC_ATTACK_TWO] = new Sprite(this->associated, "img/" + character + "/basic_attack_two.png", 19, 0.04, 0, false);
  this->sprite[COMBO] = new Sprite(this->associated, "img/" + character + "/combo.png", 18, 0.04, 0, false);
  this->sprite[ULTIMATE_BEGIN] = new Sprite(this->associated, "img/" + character + "/ultimate_begin.png", 3, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 15, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 10, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/combo.png", 18, 0.04, 0, false);

  this->ActivateSprite(IDLE);


  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_TWO]);
  this->associated.AddComponent(this->sprite[COMBO]);
  this->associated.AddComponent(this->sprite[ULTIMATE_BEGIN]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);

  this->associated.AddComponent(new Collider(this->associated, {0.7,0.8}));
}

Teacher::~Teacher() {
  Teacher::player = nullptr;
}

#include <iostream>

void Teacher::Update(float dt) { 
  Playable::Update(dt);

  this->ultimateDuration.Update(dt);

  // std::cout << this->ultimateDuration.Get() << std::endl;
  if(this->enemys.size() > 0 && this->ultimateDuration.Get() > 5) {
    for(auto &enemy : this->enemys) {
      Enemy *enemyType = (Enemy *) enemy->GetComponent("Enemy");
      enemyType->ResetSpeed();
      enemyType->SetState(IDLE);
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
  this->currentState = IDLE;

}