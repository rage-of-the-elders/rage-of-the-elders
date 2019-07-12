#include "Nurse.h"
#include "Collider.h"

Nurse::Nurse(GameObject &associated) : Enemy(associated) { 
  this->speed = 70;
  this->enemyAttackCooldown = NURSE_ATTACK_COOLDOWN;
  this->attackCooldown.Set(this->enemyAttackCooldown);
  this->attackColliderGapBasicAtacck1 = 0;
  this->rightOfsetColliderAttack = 0;
  this->leftOfsetColliderAttack = 0;

  std::string character = "nurse";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 21, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/attacking.png", 11, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 11, 0.04, 0, true);
  this->sprite[FROZEN] = new Sprite(this->associated, "img/" + character + "/idle.png", 11, TEACHER_ULTIMATE_TIME, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 11, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 21, 0.04, 0, false);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);
  this->associated.AddComponent(this->sprite[FROZEN]);


  this->ActivateSprite(MOVING);

  this->bodyColliderBox = new Collider(this->associated, {0.3,0.9});
  this->attackColliderBox = new Collider(this->associated, {0,0}, 1);
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->attackColliderBox->SetColliderType(1);
  this->sound[HURTING] = new Sound(this->associated, "audio/fighter/hurting-nurse.ogg");
  this->sound[DYING] = sound[HURTING];
}

Nurse::~Nurse() {

}

void Nurse::Update(float dt) {
  Enemy::Update(dt);
  this->bodyColliderBox->SetOffset({(this->orientation ? RIGHT -58 : 58), 0});
}

void Nurse::ResetSpeed() {
  this->speed = 70;
}

bool Nurse::Is(std::string type) {
  return (type == "Nurse" || Enemy::Is(type));
}
