#include "Veteran.h"
#include "Game.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>

Veteran *Veteran::player;
Veteran::Veteran(GameObject &associated) : Fighter(associated) {
  this->hp = VETERAN_HP;
  this->speed = VETERAN_SPEED;
  this->player = this;
  this->orientation = RIGHT;
  this->damage[BASIC_ATTACK_TWO] = 10;
  this->damage[COMBO] = 7;

  std::string character = "veteran";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 30, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/basic_attack_one.png", 12, 0.04, 0, false);
  this->sprite[BASIC_ATTACK_TWO] = new Sprite(this->associated, "img/" + character + "/basic_attack_two.png", 19, 0.04, 0, false);
  this->sprite[COMBO] = new Sprite(this->associated, "img/" + character + "/combo.png", 18, 0.04, 0, false);
  this->sprite[ULTIMATE_BEGIN] = new Sprite(this->associated, "img/" + character + "/ultimate_begin.png", 3, 0.04, 0, false);
  this->sprite[ULTIMATE_MIDLE] = new Sprite(this->associated, "img/" + character + "/ultimate_midle.png", 4, 0.04, 0, true);
  this->sprite[ULTIMATE_FINAL] = new Sprite(this->associated, "img/" + character + "/ultimate_final.png", 3, 0.04, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 15, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 10, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/combo.png", 18, 0.04, 0, false);
  // FIXME: Add dying sprite
  // this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 15, 0.2, 0, true);

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

  this->associated.AddComponent(new Collider(this->associated, {0.7,0.8}));
}

Veteran::~Veteran() {
  Veteran::player = nullptr;
}

void Veteran::Start() {}

void Veteran::ManageInput(float dt) {
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

void Veteran::HandleMovement(float) {
  if(not this->sprite[MOVING]->IsActive()) {
    this->ActivateSprite(MOVING);

    this->sound[MOVING]->Activate();
    this->sound[MOVING]->Play(-1);

  }
  if(not (InputManager::GetInstance().IsKeyDown(D_KEY) ||
          InputManager::GetInstance().IsKeyDown(A_KEY) ||
          InputManager::GetInstance().IsKeyDown(S_KEY) ||
          InputManager::GetInstance().IsKeyDown(W_KEY))) {
    this->currentState = IDLE;
    this->sound[MOVING]->Desactivate();
    this->sound[MOVING]->Stop();
  }
}

bool Veteran::Is(std::string type) {
  return (type == "Veteran" || Fighter::Is(type));
}

void Veteran::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}

bool Veteran::IsOpponent(GameObject &other) {
  return (not other.Has("Veteran"));
}
