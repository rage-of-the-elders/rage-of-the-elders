#include "Nurse.h"
#include "Collider.h"
#include "Veteran.h"

Nurse::Nurse(GameObject &associated) : Fighter(associated) {
  this->hp = NURSE_HP;
  this->speed = NURSE_SPEED;

  std::string character = "nurse";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.2, 0, true);
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/" + character + "/attacking.png", 5, 1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 2, 3, 0, true);

  this->ActivateSprite(MOVING);

  this->sprite[MOVING]->SetScaleX(1);
  this->sprite[ATTACKING]->SetScaleX(3.2);
  this->sprite[IDLE]->SetScaleX(0.3);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(new Collider(this->associated));
}

Nurse::~Nurse() {}
void Nurse::Start() {}

bool Nurse::TargetIsInRange() { // FIXME: This is not finished
  // return (this->associated.box.GetCenter().GetDistance(this->target.GetCenter()));
  return (Math::InRange(this->target.GetCenter().x, this->GetBox().GetCenter().x - 100, this->GetBox().GetCenter().x + 100));
  // && Math::InRange(this->target.y, this->GetBox().y - 10, this->GetBox().y + 10));
}

void Nurse::Update(float dt) {
  this->target = Veteran::player->GetBox();
  if (this->target.GetCenter().x < this->GetBox().GetCenter().x)
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
        this->sound[MOVING]->Activate();
        this->sound[MOVING]->Play(-1);
      }

      Vec2 direction = this->associated.box.GetCenter().GetSpeed(this->target.GetCenter());
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    } break;
    case Nurse::ATTACKING: {
      if(not this->sprite[ATTACKING]->IsActive()) {
        this->ActivateSprite(ATTACKING);
        this->sound[ATTACKING]->Play(1);
        puts("ué");
      }
      if(this->sprite[ATTACKING]->IsFinished()){
        this->currentState = MOVING;
        this->sprite[ATTACKING]->SetFrame(0);
        this->sprite[ATTACKING]->SetFinished(false);
      }
    } break;
    
    default:
      break;
  }
}

void Nurse::UpdateStateMachine() {
  if (TargetIsInRange()) {
    this->ActivateSprite(ATTACKING);
  // } else if (this->currentState == HURTING) {
    // this->ActivateSprite(SCAPING);
  } else {
    this->ActivateSprite(MOVING);
  }
}

bool Nurse::Is(std::string type) {
  return(type == "Nurse");
}

void Nurse::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}