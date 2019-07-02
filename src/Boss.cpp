#include "Boss.h"
#include "Collider.h"
#include "Veteran.h"

#include <iostream> 

Boss::Boss(GameObject &associated) : Enemy(associated) {
  this->hp = 200;
  this->speed = 600;
  // this->attackCooldown = Timer();
  // this->attackCooldown.Set(ATTACK_COOLDOWN);
  this->enemyAttackCooldown = 3;

  std::string character = "boss";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, 0.04, 0, true);
  this->sprite[FROZEN] = new Sprite(this->associated, "img/" + character + "/frozen.png", 25, TEACHER_ULTIMATE_TIME, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 25, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 25, 0.04, 0, false);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);
  this->associated.AddComponent(this->sprite[FROZEN]);


  this->ActivateSprite(MOVING);

  this->associated.AddComponent(new Collider(this->associated, {0.4,0.9}));
}

Boss::~Boss() {}

void Boss::ResetSpeed() {
  this->speed = 600;
}

bool Boss::Is(std::string type) {
  return (type == "Boss" || Enemy::Is(type));
}