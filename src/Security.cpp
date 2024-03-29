#include "Security.h"
#include "Collider.h"

Security::Security(GameObject &associated) : Enemy(associated) {
  this->speed = 115;
  this->enemyAttackCooldown = SECURITY_ATTACK_COOLDOWN;
  this->attackCooldown.Set(this->enemyAttackCooldown);
  this->attackColliderGapBasicAtacck1 = 90;
  this->rightOfsetColliderAttack = -80;
  this->leftOfsetColliderAttack = 80;
  this->attackColliderGapBasicAtacck1 = 70;

  std::string character = "security";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/attacking.png", 11, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, 0.04, 0, true);
  this->sprite[FROZEN] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, TEACHER_ULTIMATE_TIME, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 11, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 21, 0.04, 0, false);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);
  this->associated.AddComponent(this->sprite[FROZEN]);


  this->ActivateSprite(MOVING);

  this->bodyColliderBox = new Collider(this->associated, {0.35,1});
  this->attackColliderBox = new Collider(this->associated, {0.3,1}, 1);
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->attackColliderBox->SetColliderType(1);

  this->sound[HURTING] = new Sound(this->associated, "audio/fighter/hurting-security.ogg");
  this->sound[DYING] = sound[HURTING];
  // this->associated.AddComponent(new Collider(this->associated, {0.4,1}, {this->orientation ? RIGHT -1 : 1 * 40,0}));

}

Security::~Security() {

}

void Security::HandleDying(float) {
  if(not this->sprite[DYING]->IsActive()) {
    this->associated.GetComponent("Collider")->Desactivate();
    this->shadow->SetShadowScale({3.5, 1});
    this->ActivateSprite(DYING);
    this->associated.box.x += (this->orientation == RIGHT ? -200 : 80);
    this->sound[DYING]->Play(1);
  }
  if(this->sprite[DYING]->IsFinished()){
    shadow->RequestDelete();
    StageState::DecreaseEnemiesCount();
    this->associated.RequestDelete();
  }
}


void Security::Update(float dt) {
  Enemy::Update(dt);
  this->bodyColliderBox->SetOffset({(this->orientation ? RIGHT -30 : 30), 0});
}

void Security::ResetSpeed() {
  this->speed = 115;
}

bool Security::Is(std::string type) {
  return (type == "Security" || Enemy::Is(type));
}
