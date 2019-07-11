#include "Veteran.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include <iostream>

Veteran::Veteran(GameObject &associated) : Playable(associated) {
  this->hp = VETERAN_HP;
  this->speed = VETERAN_SPEED;
  this->player = this;
  this->orientation = RIGHT;
  this->leftOfsetColliderAttack = 80;
  this->rightOfsetColliderAttack = -80;
  this->attackColliderGapBasicAtacck1 = 100;
  this->attackColliderGapBasicAtacck2 = 70;
  this->damage[BASIC_ATTACK_TWO] = BASIC_ATK_2_DAMAGE;
  this->damage[COMBO] = COMBO_DAMAGE;

  std::string character = "veteran";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 21, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/basic_attack_one.png", 12, 0.04, 0, false);
  this->sprite[BASIC_ATTACK_TWO] = new Sprite(this->associated, "img/" + character + "/basic_attack_two.png", 19, 0.025, 0, false);
  this->sprite[COMBO] = new Sprite(this->associated, "img/" + character + "/combo.png", 20, 0.04, 0, false);
  this->sprite[ULTIMATE_BEGIN] = new Sprite(this->associated, "img/" + character + "/ultimate_begin.png", 3, 0.04, 0, false);
  this->sprite[ULTIMATE_MIDLE] = new Sprite(this->associated, "img/" + character + "/ultimate_midle.png", 4, 0.04, 0, true);
  this->sprite[ULTIMATE_FINAL] = new Sprite(this->associated, "img/" + character + "/ultimate_final.png", 3, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 15, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 10, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 21, 0.04, 0, false);

  this->ActivateSprite(IDLE);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_TWO]);
  this->associated.AddComponent(this->sprite[COMBO]);
  this->associated.AddComponent(this->sprite[ULTIMATE_BEGIN]);
  this->associated.AddComponent(this->sprite[ULTIMATE_MIDLE]);
  this->associated.AddComponent(this->sprite[ULTIMATE_FINAL]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);

  this->bodyColliderBox = new Collider(this->associated, {0.4,0.8});
  this->attackColliderBox = new Collider(this->associated, {0.4,0.8}, 1);
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->attackColliderBox->SetColliderType(1);
}

Veteran::~Veteran() {
  Veteran::player = nullptr;
}

void Veteran::Update(float dt) {
  Fighter::Update(dt);
  this->bodyColliderBox->SetOffset({(this->orientation == RIGHT ? 7 : -7), 0});
}

bool Veteran::Is(std::string type) {
  return (type == "Veteran" || Playable::Is(type));
}

float Veteran::GetHPPercentage() {
  return (this->hp*1.0/VETERAN_HP*1.0) * 100;
}