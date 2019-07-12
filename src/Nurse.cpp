#include "Nurse.h"
#include "Collider.h"
#include "Playable.h"
#include "Camera.h"
#include <iostream>

Nurse::Nurse(GameObject &associated) : Enemy(associated) {
  this->speed = NURSE_SPEED;
  this->enemyAttackCooldown = NURSE_ATTACK_COOLDOWN;
  this->attackCooldown.Set(0);
  this->attackColliderGapBasicAtacck1 = 0;
  this->rightOfsetColliderAttack = 0;
  this->leftOfsetColliderAttack = 0;
  this->nurseSide = LEFT_SIDE_OF_THE_SCREEN;

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
  this->attackColliderBox = new Collider(this->associated, {0.0,0.0}, 1);
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
  this->attackCooldown.Update(dt);
}

void Nurse::ResetSpeed() {
  this->speed = NURSE_SPEED;
}

bool Nurse::Is(std::string type) {
  return (type == "Nurse" || Enemy::Is(type));
}

void Nurse::ManageInput(float dt) {
  if(Playable::player != nullptr) {
    this->target = Playable::player->GetBodyCollider();
    this->tagetPlayer = Playable::player->GetFoot();

    if(this->IsDead()) {
      this->currentState = DYING;
    }

    float targetXPosition = (Camera::position.x - this->associated.box.x);
    Vec2 tagetYPosition = Vec2(Camera::position.x + 224, this->tagetPlayer.y);

    if(targetXPosition < 1) {
      if(this->attackCooldown.Get() > enemyAttackCooldown && not this->IsAttacking()) {
        this->currentState = BASIC_ATTACK_ONE;
        this->Shoot("img/nurse/shoot.png", NURSE_BULLET_FRAME_COUNT, NURSE_BULLET_DAMAGE, NURSE_BULLET_Y_GAP, BULLET_LEFT_GAP, BULLET_RIGHT_GAP, this->GetFoot().y, "Nurse", 600);
        this->attackCooldown.Restart();
      }
      else {
        Component *basicAtacckAsComponent = (Component *)(this->sprite[BASIC_ATTACK_ONE]);
        if(not basicAtacckAsComponent->IsActive()) {
          this->currentState = IDLE;
          if(not (abs(this->GetFoot().y - Playable::player->GetFoot().y) < 30)) {
            this->currentState = MOVING;
            Vec2 direction = this->GetFoot().GetCenter().GetSpeed(Vec2(this->tagetPlayer.x, this->tagetPlayer.y));
            this->associated.box.UpdatePosY(NURSE_SPEED * dt * direction.y * 2);
          }
          else {
            this->currentState = IDLE;
          }
        }
      }
    }
    else {
      Vec2 direction = this->GetFoot().GetCenter().GetSpeed(tagetYPosition);
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }

  }

  if (this->currentState != DYING) {
    if (this->target->GetCenter().x + 10 < this->GetBox().GetCenter().x)
      this->orientation = LEFT;
    else
      this->orientation = RIGHT;
    if (this->orientation == LEFT)
      this->associated.flip = SDL_FLIP_HORIZONTAL;
    else
      this->associated.flip = SDL_FLIP_NONE;
  }
}

void Nurse::HandleMovement(float dt) {
    if(not this->sprite[MOVING]->IsActive()) {
      this->ActivateSprite(MOVING);
    }
}
void Nurse::HandleHurting(float) {
  if(not this->sprite[HURTING]->IsActive()) {
    this->ActivateSprite(HURTING);
  }
  if(this->sprite[HURTING]->IsFinished()) {
    this->sprite[HURTING]->SetFrame(0);
    this->sprite[HURTING]->SetFinished(false);
    if(this->associated.Has("Boss"))
      this->currentState = FROZEN;
    else
      this->currentState = MOVING;
    this->storedState = INVALID;

    if(this->nurseSide == LEFT_SIDE_OF_THE_SCREEN) {
      this->nurseSide = RIGHT_SIDE_OF_THE_SCREEN;
    }
    else {
      this->nurseSide = LEFT_SIDE_OF_THE_SCREEN;
    }
  }
}
