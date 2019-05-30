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
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/" + character + "/attacking.png", 50, 0.1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 30, 0.2, 0, true);

  this->ActivateSprite(IDLE);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
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
  if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    this->currentState = ATTACKING;
  }
  if(InputManager::GetInstance().IsKeyDown(D_KEY)) {
    this->currentState = MOVING;
    Vec2 direction = Vec2::GetSpeed(0); // FIXME: This shouldn't be here. Move to Update
    this->associated.box.UpdatePos((direction * this->speed) * dt);
    this->orientation = RIGHT;
  }
  if(InputManager::GetInstance().IsKeyDown(A_KEY)){
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
    case Veteran::ATTACKING: {
      if(not this->sprite[ATTACKING]->IsActive()) {
        this->ActivateSprite(ATTACKING);
        this->sound[ATTACKING]->Play(1);
      }
      if(this->sprite[ATTACKING]->IsFinished()){
        this->currentState = IDLE;
        this->sprite[ATTACKING]->SetFrame(0);
        this->sprite[ATTACKING]->SetFinished(false);
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