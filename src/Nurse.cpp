#include "Nurse.h"
#include "Collider.h"
#include "Veteran.h"

#include <iostream>

Nurse::Nurse(GameObject &associated) : Fighter(associated) {
  this->hp = NURSE_HP;
  this->speed = NURSE_SPEED;

  std::string character = "nurse";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 21, 0.4, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/attacking.png", 11, 0.09, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 11, 0.09, 0, true);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[MOVING]);

  this->ActivateSprite(MOVING);

  this->associated.AddComponent(new Collider(this->associated));
}

Nurse::~Nurse() {}
void Nurse::Start() {}

bool Nurse::TargetIsInRange() {
  float nurseAttackX = this->sprite[BASIC_ATTACK_ONE]->GetBox().GetCenter().x;
  float nurseAttackY = (this->associated.box.y + this->associated.box.h);
  float nurseAttackWidth = this->sprite[BASIC_ATTACK_ONE]->GetWidth();
  float nurseXRange = (nurseAttackWidth/2.0) + (this->target.w/2.0);

  float targetDistanceX = abs(target.GetCenter().x - nurseAttackX);
  float targetDistanceY = abs((target.y + target.h) - nurseAttackY);

  // std::cout << "nurseAttackX: " << nurseAttackX << std::endl;
  // std::cout << "nurseAttackWidth: " << nurseAttackWidth << std::endl;
  // std::cout << "nurseXRange: " << nurseXRange << std::endl;
  // std::cout << "targetDistanceX: " << targetDistanceX << std::endl;
  // std::cout << "targetDistanceY: " << targetDistanceY << std::endl;
  // std::cout << "targetX: " << target.x << std::endl;

  return((nurseXRange > targetDistanceX) && (ATTACK_Y_RANGE > targetDistanceY));
}

void Nurse::Update(float dt) {
  this->target = Veteran::player->GetBox();

  if (this->target.GetCenter().x + 10 < this->GetBox().GetCenter().x)
    this->orientation = LEFT;
  else
    this->orientation = RIGHT;

  if (this->orientation == LEFT)
    this->associated.flip = SDL_FLIP_HORIZONTAL;
  else
    this->associated.flip = SDL_FLIP_NONE;

  this->UpdateStateMachine();

  switch (this->currentState) {
    case Nurse::MOVING: {
      if(not this->sprite[MOVING]->IsActive()) {

        this->ActivateSprite(MOVING);

        this->sound[MOVING]->Play(-1);
      }

      Vec2 direction = this->associated.box.GetCenter().GetSpeed(this->target.GetCenter());
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    } break;
    case Nurse::BASIC_ATTACK_ONE: {
      if(not this->sprite[BASIC_ATTACK_ONE]->IsActive()) {
        this->ActivateSprite(BASIC_ATTACK_ONE);
        this->sound[BASIC_ATTACK_ONE]->Play(1);
      }
      if(this->sprite[BASIC_ATTACK_ONE]->IsFinished()){
        this->sprite[BASIC_ATTACK_ONE]->SetFrame(0);
        this->sprite[BASIC_ATTACK_ONE]->SetFinished(false);
        this->currentState = MOVING;
      }
    } break;

    default:
      break;
  }
}

void Nurse::UpdateStateMachine() {
  if (TargetIsInRange()) {
    this->currentState = BASIC_ATTACK_ONE;
    }
  else {
    if(this->sprite[MOVING]->IsActive())
      if(this->sprite[MOVING]->IsFinished())
        this->currentState = MOVING;
  }
}

bool Nurse::Is(std::string type) {
  return(type == "Nurse");
}

void Nurse::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}
