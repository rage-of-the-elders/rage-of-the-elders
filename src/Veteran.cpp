#include "Veteran.h"
#include "Game.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>

Veteran::Veteran(GameObject &associated) : Fighter(associated) {
  this->hp = VETERAN_HP;
  this->speed = VETERAN_SPEED;

  std::string character = "veteran";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 42, 0.1, 0, true);
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/" + character + "/attacking.png", 5, 1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 2, 3, 0, true);

  this->ActivateSprite(IDLE);

  this->sprite[MOVING]->SetScaleX(0.6);
  this->sprite[ATTACKING]->SetScaleX(2.4);
  this->sprite[IDLE]->SetScaleX(0.3);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
  this->associated.AddComponent(this->sprite[MOVING]);
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
    this->speed = Vec2::GetSpeed(0); // FIXME: This shouldn't be here. Move to Update
    this->associated.box.UpdatePos((speed*10) * dt);
    this->orientation = RIGHT;
  }
  if(InputManager::GetInstance().IsKeyDown(A_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(0);
    this->associated.box.UpdatePos((speed*-20) * dt);
    this->orientation = LEFT;
  }
  if(InputManager::GetInstance().IsKeyDown(S_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(90);
    this->associated.box.UpdatePos((speed*20) * dt);
  }
  if(InputManager::GetInstance().IsKeyDown(W_KEY)){
    this->currentState = MOVING;
    this->speed = Vec2::GetSpeed(270);
    this->associated.box.UpdatePos((speed*20) * dt);
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

void Veteran::Render() {
  Vec2 center(this->associated.box.GetCenter());
  SDL_Point points[5];

  Vec2 point = (Vec2(this->associated.box.GetFoot().x, this->associated.box.GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(this->associated.box.GetFoot().x + this->associated.box.GetFoot().w, this->associated.box.GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(this->associated.box.GetFoot().x + this->associated.box.GetFoot().w, this->associated.box.GetFoot().y + this->associated.box.GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(this->associated.box.GetFoot().x, this->associated.box.GetFoot().y + this->associated.box.GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

bool Veteran::Is(std::string type) {
  return(type == "Veteran");
}

void Veteran::NotifyCollision(GameObject &other) {

  Rect VeteranFoot = this->associated.box.GetFoot();

  if(Collision::IsColliding(VeteranFoot, other.box, this->associated.angleDeg, other.angleDeg)) {
    
    float collisionX = std::min( abs(VeteranFoot.x + VeteranFoot.w - other.box.x), abs(VeteranFoot.x - (other.box.x + other.box.w)));
    float collisionY = std::min( abs(VeteranFoot.y + VeteranFoot.h - other.box.y), abs(VeteranFoot.y - (other.box.y + other.box.h)));

    if( collisionX > collisionY) {
      
      float objY;

      float distanceToBottom = VeteranFoot.y - (abs(other.box.y) + other.box.h);

      float distanceToTop = (VeteranFoot.y + VeteranFoot.h) - abs(other.box.y);

      if(abs(distanceToBottom) > abs(distanceToTop)) {
        objY = other.box.y;

        if( (VeteranFoot.y + VeteranFoot.h) > objY ) {
          this->associated.box.y = other.box.y - this->associated.box.h;
        }
      }
      else {
        objY = other.box.y + other.box.h;

        if( VeteranFoot.y < objY ) {
          this->associated.box.y = other.box.y + other.box.h - this->associated.box.h + VeteranFoot.h;
        }
      }
    }
    else {

      float objX;

      float distanceToRight = VeteranFoot.x - (abs(other.box.x) + other.box.w);

      float distanceToLeft = (VeteranFoot.x + VeteranFoot.w) - abs(other.box.x);

      if(abs(distanceToRight) > abs(distanceToLeft)) {
        objX = other.box.x;

        if( (VeteranFoot.x + VeteranFoot.w) > objX ) {
          this->associated.box.x = other.box.x - VeteranFoot.w;
        }
      }
      else{
        objX = other.box.x + other.box.w;

        if( VeteranFoot.x < objX ) {
          this->associated.box.x = other.box.x + other.box.w;
        }
      }
    }
  }
}

void Veteran::ActivateSprite(VeteranState state) {
  for(int enumState = FIRST; enumState < this->LAST; enumState++) {
    VeteranState currentEnumState = static_cast<VeteranState>(enumState);
    if (currentEnumState == state) {
      sprite[state]->Activate();
    } else if (currentEnumState != FIRST && currentEnumState != LAST){
      sprite[currentEnumState]->Desactivate();
    }
  }
}