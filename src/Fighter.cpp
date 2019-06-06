#include "Fighter.h"
#include "Camera.h"
#include "Game.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Collision.h"
#include <iostream>

Fighter::Fighter(GameObject &associated) : Component(associated) {
  this->hp = FIGHTER_HP; // Maybe we should receive this on the constructor
  this->speed = FIGHTER_SPEED; // Maybe we should receive this on the constructor
  this->currentState = IDLE;
  this->orientation = LEFT;
  this->active = true;
  this->isTakingDamage = false;
  this->storedState = INVALID;

  this->sprite = std::vector<Sprite*>(LAST);
  this->sound = std::vector<Sound*>(LAST);

  this->sound[MOVING] = new Sound(this->associated, "audio/walking.ogg");
  this->sound[BASIC_ATTACK_ONE] = new Sound(this->associated, "audio/boom.wav");
  this->sound[BASIC_ATTACK_TWO] = new Sound(this->associated, "audio/boom.wav");
  this->sound[COMBO] = new Sound(this->associated, "audio/boom.wav");
  this->sound[ULTIMATE] = new Sound(this->associated, "audio/boom.wav");

  this->associated.AddComponent(this->sound[MOVING]);
  this->associated.AddComponent(this->sound[BASIC_ATTACK_ONE]);

}

Fighter::~Fighter() {}
void Fighter::Start() {}
void Fighter::Update(float) {}

void Fighter::Render() {
  #ifdef DEBUG
  
  Vec2 center(this->associated.box.GetCenter());
  SDL_Point points[5];

  Vec2 point = (Vec2(this->GetFoot().x, this->GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x + this->GetFoot().w, this->GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x + this->GetFoot().w, this->GetFoot().y + this->GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x, this->GetFoot().y + this->GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
  
  #endif
}

bool Fighter::Is(std::string type) {
  return(type == "Fighter");
}

void Fighter::NotifyCollision(GameObject &other) {

  if(other.Has("Barrier")) {

    Collider *colliderBox = (Collider*) this->associated.GetComponent("Collider");


    Rect fighterFoot = this->GetFoot();

    if(Collision::IsColliding(fighterFoot, other.box, this->associated.angleDeg, other.angleDeg)) {
      
      float collisionX = std::min( abs(fighterFoot.x + fighterFoot.w - other.box.x), abs(fighterFoot.x - (other.box.x + other.box.w)));
      float collisionY = std::min( abs(fighterFoot.y + fighterFoot.h - other.box.y), abs(fighterFoot.y - (other.box.y + other.box.h)));

      if( collisionX > collisionY) {
        
        float objY;

        float distanceToBottom = fighterFoot.y - (other.box.y + other.box.h);

        float distanceToTop = (fighterFoot.y + fighterFoot.h) - other.box.y;

        if(abs(distanceToBottom) > abs(distanceToTop)) {
          objY = other.box.y;

          if( (fighterFoot.y + fighterFoot.h) > objY ) {
            this->associated.box.y = other.box.y - ((this->associated.box.h - colliderBox->GetHeigth()) /2) -
            colliderBox->GetHeigth();
          }
        }
        else {
          objY = other.box.y + other.box.h;

          if( fighterFoot.y < objY ) {
            this->associated.box.y = other.box.y + other.box.h -
            ((this->associated.box.h - colliderBox->GetHeigth()) /2) -
            colliderBox->GetHeigth() + fighterFoot.h;
          }
        }
      }
      else {

        float objX;

        float distanceToRight = fighterFoot.x - (abs(other.box.x) + other.box.w);

        float distanceToLeft = (fighterFoot.x + fighterFoot.w) - abs(other.box.x);

        if(abs(distanceToRight) > abs(distanceToLeft)) {
          objX = other.box.x;

          if( (fighterFoot.x + fighterFoot.w) > objX ) {
            this->associated.box.x = other.box.x - colliderBox->GetWidth() - ((this->associated.box.w - colliderBox->GetWidth()) /2);
          }
        }
        else{
          objX = other.box.x + other.box.w;

          if( fighterFoot.x < objX ) {
            this->associated.box.x = other.box.x + other.box.w - ((this->associated.box.w - colliderBox->GetWidth()) /2);
          }
        }
      }
    }
  }
}

void Fighter::ActivateSprite(FighterState state) {
  for(int enumState = FIRST; enumState < this->LAST; enumState++) {
    FighterState currentEnumState = static_cast<FighterState>(enumState);
    if (currentEnumState == state) {
      this->currentState = state;
      sprite[state]->Activate();
    } else if (sprite[enumState]){
      sprite[currentEnumState]->Desactivate();
    }
  }
}

Rect Fighter::GetFoot() {
  Collider *colliderBox = (Collider*) this->associated.GetComponent("Collider");
  return Rect(colliderBox->GetX(), ((colliderBox->GetY() + colliderBox->GetHeigth()) - 10), colliderBox->GetWidth(), 10);
}

bool Fighter::IsAttacking(){
  return(Math::InRange(currentState, BASIC_ATTACK_ONE, ULTIMATE));
}

void Fighter::ApplyDamage(int damage){
  this->hp -=damage;
}

bool Fighter::IsHurting(){
  return(currentState == HURTING);
}

bool Fighter::CanAttack(enum Orientation targetOrientation, Rect targetRect) {
  if((targetOrientation == Fighter::LEFT && (this->associated.box.x < targetRect.x)) ||
    targetOrientation == Fighter::RIGHT && (this->associated.box.x > targetRect.x))
    return true;
  
  return false;
}