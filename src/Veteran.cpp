#include "Veteran.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include<iostream>

Veteran::Veteran(GameObject &associated) : Component(associated) {
  this->hp = VETERAN_HP;
  this->speed = VETERAN_SPEED;
  this->currentState = IDLE;
  this->active = true;

  this->sprite = std::vector<Sprite*>(IDLE);
  this->sound = std::vector<Sound*>(IDLE);

  this->sprite[MOVING] = new Sprite(this->associated, "img/veteran2.png", 24, 0.3, 0, true);
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/veteran4.png", 4, 4, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/veteran3.png", 2, 8, 0, true);

  this->sprite[IDLE]->Activate();
  this->sprite[ATTACKING]->Desactivate();
  this->sprite[MOVING]->Desactivate();

  this->sprite[MOVING]->SetScaleX(0.3);
  this->sprite[ATTACKING]->SetScaleX(2);
  this->sprite[IDLE]->SetScaleX(0.3);

  this->sound[MOVING] = new Sound(this->associated, "audio/boom.wav");
  this->sound[ATTACKING] = new Sound(this->associated, "audio/boom.wav");

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
  this->associated.AddComponent(this->sprite[MOVING]);

  this->associated.AddComponent(this->sound[MOVING]);
  this->associated.AddComponent(this->sound[ATTACKING]);


  this->associated.AddComponent(new Collider(this->associated));
}

Veteran::~Veteran() {

}

void Veteran::Start() {

}

void Veteran::Update(float dt) {
  if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
      this->currentState = ATTACKING;
  }
  else if(InputManager::GetInstance().IsKeyDown(D_KEY)) {
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(0);
    this->associated.box.UpdatePos((speed*10) * dt);

    if(InputManager::GetInstance().IsKeyDown(W_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(45);
      this->associated.box.UpdatePos((speed*-10) * dt);
    }
    else if(InputManager::GetInstance().IsKeyDown(S_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(135);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
  }
  else if(InputManager::GetInstance().IsKeyDown(A_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(0);
    this->associated.box.UpdatePos((speed*-10) * dt);
    
    if(InputManager::GetInstance().IsKeyDown(W_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(315);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
    else if(InputManager::GetInstance().IsKeyDown(S_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(45);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
  }
  else if(InputManager::GetInstance().IsKeyDown(S_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(90);
    this->associated.box.UpdatePos((speed*10) * dt);

    if(InputManager::GetInstance().IsKeyDown(A_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(45);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
    else if(InputManager::GetInstance().IsKeyDown(D_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(135);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
  }
  else if(InputManager::GetInstance().IsKeyDown(W_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(270);
    this->associated.box.UpdatePos((speed*10) * dt);

    if(InputManager::GetInstance().IsKeyDown(A_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(315);
      this->associated.box.UpdatePos((speed*10) * dt);
    }
    else if(InputManager::GetInstance().IsKeyDown(D_KEY)){
      // this->currentState = MOVING;
      this->speed = Vec2::GetSpeed(45);
      this->associated.box.UpdatePos((speed*-10) * dt);
    }
  }

  switch (this->currentState) {
    case Veteran::MOVING: {
      if(not this->sprite[MOVING]->IsActive()) {
        this->sprite[IDLE]->Desactivate();
        this->sprite[ATTACKING]->Desactivate();
        this->sprite[MOVING]->Activate();

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
        this->sprite[MOVING]->Desactivate();
        this->sprite[ATTACKING]->Desactivate();   
        this->sprite[IDLE]->Activate();
      }
    } break;
    case Veteran::ATTACKING: {
      if(not this->sprite[ATTACKING]->IsActive()) {
        this->sprite[MOVING]->Desactivate();
        this->sprite[IDLE]->Desactivate();
        this->sprite[ATTACKING]->Activate();

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

void Veteran::Render() {

}

bool Veteran::Is(std::string type) {
  return(type == "Veteran");
}

void Veteran::NotifyCollision(GameObject &other) {

}