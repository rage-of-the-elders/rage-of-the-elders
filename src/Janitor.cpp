#include "Janitor.h"
#include "Collider.h"

Janitor::Janitor(GameObject &associated) : Enemy(associated) {

  this->rightOfsetColliderAttack = -150;
  this->leftOfsetColliderAttack = 150;
  this->attackColliderGapBasicAtacck1 = 100;

  std::string character = "janitor";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/attacking.png", 16, 0.04, 0, false);
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

  this->bodyColliderBox = new Collider(this->associated, {0.2,1});
  this->attackColliderBox = new Collider(this->associated, {0.3,1}, 1);
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->attackColliderBox->SetColliderType(1);
  // this->associated.AddComponent(new Collider(this->associated, {0.4,1}, {this->orientation ? RIGHT -1 : 1 * 60,0}));

}

Janitor::~Janitor() {

}

void Janitor::HandleDying(float) {
  if(not this->sprite[DYING]->IsActive()) {
    this->associated.GetComponent("Collider")->Desactivate();
    this->ActivateSprite(DYING);
    this->associated.box.x += (this->orientation == RIGHT ? 60 : -320);
    this->associated.box.y += (this->orientation == RIGHT ? 30 : 30);
    // this->sound[DYING]->Play(1);
  }
  if(this->sprite[DYING]->IsFinished()){
    StageState::DecreaseEnemiesCount();
    this->associated.RequestDelete();
  }
}

void Janitor::Update(float dt) {
  Enemy::Update(dt);
  this->bodyColliderBox->SetOffset({(this->orientation ? RIGHT -75 : 75), 0});
}

void Janitor::ResetSpeed() {
  this->speed = ENEMY_SPEED;
}

bool Janitor::Is(std::string type) {
  return (type == "Janitor" || Enemy::Is(type));
}
