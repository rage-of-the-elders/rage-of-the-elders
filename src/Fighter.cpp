#include "Fighter.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include <iostream>

Fighter::Fighter(GameObject &associated, std::string character) : Component(associated) {
  this->hp = FIGHTER_HP; // Maybe we should receive this on the constructor
  this->speed = FIGHTER_SPEED; // Maybe we should receive this on the constructor
  this->currentState = IDLE;
  this->orientation = RIGHT;
  this->active = true;

  this->sprite = std::vector<Sprite*>(LAST);
  this->sound = std::vector<Sound*>(LAST);

  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 42, 0.1, 0, true);
  this->sprite[ATTACKING] = new Sprite(this->associated, "img/" + character + "/attacking.png", 5, 1, 0, false);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 2, 3, 0, true);

  this->ActivateSprite(IDLE);

  this->sprite[MOVING]->SetScaleX(0.6);
  this->sprite[ATTACKING]->SetScaleX(2.4);
  this->sprite[IDLE]->SetScaleX(0.3);

  this->sound[MOVING] = new Sound(this->associated, "audio/walking.ogg");
  this->sound[ATTACKING] = new Sound(this->associated, "audio/boom.wav");

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[ATTACKING]);
  this->associated.AddComponent(this->sprite[MOVING]);

  this->associated.AddComponent(this->sound[MOVING]);
  this->associated.AddComponent(this->sound[ATTACKING]);
  this->associated.AddComponent(new Collider(this->associated));
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
      sprite[state]->Activate();
    } else if (currentEnumState != FIRST && currentEnumState != LAST){
      sprite[currentEnumState]->Desactivate();
    }
  }
}