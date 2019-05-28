#include "Fighter.h"
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

  this->sprite = std::vector<Sprite*>(LAST);
  this->sound = std::vector<Sound*>(LAST);

  this->sound[MOVING] = new Sound(this->associated, "audio/walking.ogg");
  this->sound[ATTACKING] = new Sound(this->associated, "audio/boom.wav");

  this->associated.AddComponent(this->sound[MOVING]);
  this->associated.AddComponent(this->sound[ATTACKING]);

  this->associated.AddComponent(new Collider(this->associated));
}

Fighter::~Fighter() {}
void Fighter::Start() {}
void Fighter::Update(float) {}
void Fighter::Render() {}

bool Fighter::Is(std::string type) {
  return(type == "Fighter");
}

void Fighter::NotifyCollision(GameObject &other) {
  Rect VeteranFoot = this->associated.box.GetFoot();

  if(Collision::IsColliding(VeteranFoot, other.box, this->associated.angleDeg, other.angleDeg)) {
    
    float collisionX = std::min( abs(VeteranFoot.x + VeteranFoot.w - other.box.x), abs(VeteranFoot.x - (other.box.x + other.box.w)));
    float collisionY = std::min( abs(VeteranFoot.y + VeteranFoot.h - other.box.y), abs(VeteranFoot.y - (other.box.y + other.box.h)));

    if( collisionX > collisionY) {
      
      float objY;

      float distanceToBottom = VeteranFoot.y - (other.box.y + other.box.h);

      float distanceToTop = (VeteranFoot.y + VeteranFoot.h) - other.box.y;

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

void Fighter::ActivateSprite(FighterState state) {
  for(int enumState = FIRST; enumState < this->LAST; enumState++) {
    FighterState currentEnumState = static_cast<FighterState>(enumState);
    if (currentEnumState == state) {
      this->currentState = state;
      sprite[state]->Activate();
    } else if (currentEnumState != FIRST && currentEnumState != LAST){
      sprite[currentEnumState]->Desactivate();
    }
  }
}