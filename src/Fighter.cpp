#include "Fighter.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
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
}

Fighter::~Fighter() {}
void Fighter::Start() {}
void Fighter::Update(float dt) {}
void Fighter::Render() {}

bool Fighter::Is(std::string type) {
  return(type == "Fighter");
}

void Fighter::NotifyCollision(GameObject &other) {}

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