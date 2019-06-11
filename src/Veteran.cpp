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

  std::string character = "veteran";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 30, 0.15, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/basic_attack_one.png", 15, 0.1, 0, false);
  this->sprite[BASIC_ATTACK_TWO] = new Sprite(this->associated, "img/" + character + "/basic_attack_two.png", 19, 0.1, 0, false);
  this->sprite[COMBO] = new Sprite(this->associated, "img/" + character + "/combo.png", 18, 0.1, 0, false);
  this->sprite[ULTIMATE] = new Sprite(this->associated, "img/" + character + "/ultimate.png", 50, 0.1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 15, 0.2, 0, true);

  this->ActivateSprite(IDLE);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_TWO]);
  this->associated.AddComponent(this->sprite[COMBO]);
  this->associated.AddComponent(this->sprite[ULTIMATE]);
  this->associated.AddComponent(this->sprite[MOVING]);

  this->associated.AddComponent(new Collider(this->associated));
}

Veteran::~Veteran() {

}

void Veteran::Start() {

}

void Veteran::Update(float dt) {
  this->ManageInput(dt);
  this->UpdateStateMachine();
}

void Veteran::ManageInput(float dt) {
  if(InputManager::GetInstance().KeyPress(F_KEY)) {
    this->currentState = BASIC_ATTACK_ONE;
  }
  else if(InputManager::GetInstance().KeyPress(G_KEY)) {
    this->currentState = BASIC_ATTACK_TWO;
  }
  else if(InputManager::GetInstance().KeyPress(H_KEY)) {
    this->currentState = COMBO;
  }
  else if(InputManager::GetInstance().KeyPress(J_KEY)) {
    this->currentState = ULTIMATE;
    Camera::Flicker(9.3, 0.3);
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

void Veteran::UpdateStateMachine() {
  if(this->orientation == LEFT)
    this->associated.flip = SDL_FLIP_HORIZONTAL;
  else
    this->associated.flip = SDL_FLIP_NONE;

  switch (this->currentState) {
    case Veteran::MOVING: {
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
    } break;
    case Veteran::IDLE: {
      if(not this->sprite[IDLE]->IsActive()) {
        this->ActivateSprite(IDLE);
      }
    } break;
    case Veteran::BASIC_ATTACK_ONE: {
      if(not this->sprite[BASIC_ATTACK_ONE]->IsActive()) {
        this->ActivateSprite(BASIC_ATTACK_ONE);
        this->sound[BASIC_ATTACK_ONE]->Play(1);
      }
      if(this->sprite[BASIC_ATTACK_ONE]->IsFinished()) {
        this->currentState = IDLE;
        this->sprite[BASIC_ATTACK_ONE]->SetFrame(0);
        this->sprite[BASIC_ATTACK_ONE]->SetFinished(false);
      }
    } break;
    case Veteran::BASIC_ATTACK_TWO: {
      if(not this->sprite[BASIC_ATTACK_TWO]->IsActive()) {
        this->ActivateSprite(BASIC_ATTACK_TWO);
        this->sound[BASIC_ATTACK_TWO]->Play(1);
      }
      if(this->sprite[BASIC_ATTACK_TWO]->IsFinished()) {
        this->currentState = IDLE;
        this->sprite[BASIC_ATTACK_TWO]->SetFrame(0);
        this->sprite[BASIC_ATTACK_TWO]->SetFinished(false);
      }
    } break;
    case Veteran::COMBO: {
      if(not this->sprite[COMBO]->IsActive()) {
        this->ActivateSprite(COMBO);
        this->sound[COMBO]->Play(1);
      }
      if(this->sprite[COMBO]->IsFinished()) {
        this->currentState = IDLE;
        this->sprite[COMBO]->SetFrame(0);
        this->sprite[COMBO]->SetFinished(false);
      }
    } break;
    case Veteran::ULTIMATE: {
      if(not this->sprite[ULTIMATE]->IsActive()) {
        this->ActivateSprite(ULTIMATE);
        this->sound[ULTIMATE]->Play(1);
      }
      if(this->sprite[ULTIMATE]->IsFinished()) {
        this->currentState = IDLE;
        this->sprite[ULTIMATE]->SetFrame(0);
        this->sprite[ULTIMATE]->SetFinished(false);
      }
    } break;
    default:
      break;
  }
}

bool Veteran::Is(std::string type) {
  return(type == "Veteran");
}

void Veteran::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}
