#include "Nurse.h"
#include "Collider.h"
#include "Veteran.h"

#include <iostream>

Nurse::Nurse(GameObject &associated) : Fighter(associated) {
  this->hp = NURSE_HP;
  this->speed = NURSE_SPEED;

  std::string character = "nurse";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 26, 0.2, 0, true);
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/" + character + "/attacking.png", 26, 0.1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 26, 3, 0, true);


  this->sprite[MOVING]->SetScaleX(0.5);
  this->sprite[ATTACKING]->SetScaleX(0.5);
  this->sprite[IDLE]->SetScaleX(0.5);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
  this->associated.AddComponent(this->sprite[MOVING]);
  
  this->ActivateSprite(MOVING);
  
  this->associated.AddComponent(new Collider(this->associated));
}

Nurse::~Nurse() {}
void Nurse::Start() {}

bool Nurse::TargetIsInRange() { // FIXME: This is not finished
  float nurseAttackX = this->sprite[ATTACKING]->GetBox().GetCenter().x;
  float nurseAttackY = (this->sprite[ATTACKING]->GetBox().y + this->sprite[ATTACKING]->GetWidth());
  float nurseAttackWidth = this->sprite[ATTACKING]->GetWidth();
  float nurseXRange = (nurseAttackWidth/2.0) + (this->target.w/2.0);

  float targetDistanceX = abs(target.GetCenter().x - nurseAttackX);
  float targetDistanceY = abs((target.y + target.h) - nurseAttackY);

  // std::cout << "nurseAttackX: " << nurseAttackX << std::endl;
  // std::cout << "nurseAttackWidth: " << nurseAttackWidth << std::endl;
  std::cout << "nurseXRange: " << nurseXRange << std::endl;
  std::cout << "targetDistanceX: " << targetDistanceX << std::endl;
  std::cout << "targetDistanceY: " << targetDistanceY << std::endl;
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
    case Nurse::ATTACKING: {
      if(not this->sprite[ATTACKING]->IsActive()) {
        this->ActivateSprite(ATTACKING);
        this->sound[ATTACKING]->Play(1);
      }
      if(this->sprite[ATTACKING]->IsFinished()){
        this->sprite[ATTACKING]->SetFrame(0);
        this->sprite[ATTACKING]->SetFinished(false);
        this->currentState = MOVING;
      }
    } break;
    
    default:
      break;
  }
}

void Nurse::UpdateStateMachine() {
  if (TargetIsInRange()) {
    this->currentState = ATTACKING;
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