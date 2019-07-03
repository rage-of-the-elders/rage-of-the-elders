#include "Playable.h"
#include "Game.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>

Playable *Playable::player;
Playable::Playable(GameObject &associated) : Fighter(associated) {
  this->hp = PLAYABLE_HP;
  this->speed = PLAYABLE_SPEED;
  // this->player = this;
  this->orientation = RIGHT;
  this->damage[BASIC_ATTACK_TWO] = 10;
  this->damage[COMBO] = 7;
}

Playable::~Playable() {
  // Playable::player = nullptr;
}
void Playable::Update(float dt) {
  Fighter::Update(dt);
}

void Playable::Start() {}

void Playable::ManageInput(float dt) {
  if (this->IsDead()) {
    this->currentState = DYING;
  } else {
    if((InputManager::GetInstance().GetLastsPressKeys() == "FG") && (not this->IsAttacking())) {
      this->currentState = COMBO;

      InputManager::GetInstance().SetLastsPressKeys("");
    }
    else if(InputManager::GetInstance().KeyPress(F_KEY) && (not this->IsAttacking())) {
      this->currentState = BASIC_ATTACK_ONE;
    }
    else if(InputManager::GetInstance().KeyPress(G_KEY) && (not this->IsAttacking())) {
      this->currentState = BASIC_ATTACK_TWO;
    }
    else if(InputManager::GetInstance().KeyPress(J_KEY) && (not this->IsAttacking())) {
      this->currentState = ULTIMATE_BEGIN;
      Camera::Flicker(5, 0.3);
    }
    else if(InputManager::GetInstance().IsKeyDown(D_KEY)) {
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(0); // FIXME: This shouldn't be here. Move to Update
      this->associated.box.UpdatePos((direction * this->speed) * dt);
      this->orientation = RIGHT;
    }
    else if(InputManager::GetInstance().IsKeyDown(A_KEY)){
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(0);
      this->associated.box.UpdatePos((direction * -this->speed) * dt);
      this->orientation = LEFT;
    }
    if(InputManager::GetInstance().IsKeyDown(S_KEY)){
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(90);
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }
    if(InputManager::GetInstance().IsKeyDown(W_KEY)){
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(270);
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }
  }

  if(this->orientation == LEFT)
    this->associated.flip = SDL_FLIP_HORIZONTAL;
  else
    this->associated.flip = SDL_FLIP_NONE;
}

// void Veteran::UpdateStateMachine(float dt) {
//   Fighter::UpdateStateMachine(dt);
//   printf("veteran: %d\n", this->hp);
// }

void Playable::HandleMovement(float) {
  if(not this->sprite[MOVING]->IsActive()) {
    this->ActivateSprite(MOVING);

    this->sound[MOVING]->Activate();
    // TODO: Add PlayIfNotPlaying()
    // if (not this->sound[MOVING]->IsPlaying())
      this->sound[MOVING]->Play(-1);

  }
  if(not (InputManager::GetInstance().IsKeyDown(D_KEY) ||
          InputManager::GetInstance().IsKeyDown(A_KEY) ||
          InputManager::GetInstance().IsKeyDown(S_KEY) ||
          InputManager::GetInstance().IsKeyDown(W_KEY))) {
    this->currentState = IDLE;
    this->sound[MOVING]->Stop();
  }
}

bool Playable::Is(std::string type) {
  return (type == "Playable" || Fighter::Is(type));
}

void Playable::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}

bool Playable::IsOpponent(GameObject &other) {
  return (not other.Has("Playable"));
}

void Playable::HandleUltimateBegin(float dt) {
  Fighter::HandleUltimateBegin(dt);
}
void Playable::HandleUltimateMidle(float dt) {
  Fighter::HandleUltimateMidle(dt);
}
void Playable::HandleUltimateFinal(float dt) {
  Fighter::HandleUltimateFinal(dt);
}