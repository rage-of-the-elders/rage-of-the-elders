#include "Playable.h"
#include "Game.h"
#include "Collision.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <iostream>

Playable *Playable::player;
Playable::Playable(GameObject &associated) : Fighter(associated) {
  this->hp = PLAYABLE_HP;
  this->speed = PLAYABLE_SPEED;
  // this->player = this;
  this->orientation = RIGHT;
  this->damage[BASIC_ATTACK_TWO] = 10;
  this->damage[COMBO] = 7;
  this->ultimateBarSpriteNumber = -1;
  this->points = 0;

  this->infoBar = new GameObject();
  this->infoBar->AddComponent(new Sprite(*infoBar, "img/playable/infobar.png"));
  this->infoBar->AddComponent(new CameraFollower(*infoBar));
  Game::GetInstance().GetCurrentState().AddObject(infoBar);

  float iconXPos = ICONS_INITIAL_X_POS;
  this->picture = new GameObject();
  this->picture->AddComponent(new Sprite(*picture, "img/playable/picture.png"));
  this->picture->AddComponent(new CameraFollower(*picture, {iconXPos, ICONS_Y_POS}));
  iconXPos += picture->box.w + ICON_SPACING;
  Game::GetInstance().GetCurrentState().AddObject(picture);


  for (int i=0; i < HEARTS_COUNTER; i++) {
    this->hearts[i] = new GameObject();
    this->hearts[i]->AddComponent(new Sprite(*hearts[i], "img/playable/heart.png", 10, 0.04));
    this->hearts[i]->AddComponent(new CameraFollower(*hearts[i], {iconXPos, ICONS_Y_POS}));
    iconXPos += hearts[i]->box.w + ICON_SPACING;
    Game::GetInstance().GetCurrentState().AddObject(hearts[i]);
  }

  this->ultimateBar = new GameObject();
  this->ultimateBarSprite = new Sprite(*ultimateBar, "img/playable/ult1.png");
  this->ultimateBar->AddComponent(ultimateBarSprite);
  this->ultimateBar->AddComponent(new CameraFollower(*ultimateBar, {10, ICONS_Y_POS + 20}));
  iconXPos += this->ultimateBar->box.w + ICON_SPACING;
  Game::GetInstance().GetCurrentState().AddObject(this->ultimateBar);
}

Playable::~Playable() {
  // Playable::player = nullptr;
}
void Playable::Update(float dt) {
  Fighter::Update(dt);
}

void Playable::Start() {}

void Playable::UpdateUltimateBarSprite(int spriteNumber) {
  if (spriteNumber <= 6) {
    Sprite *newUltimateSprite = new Sprite(*ultimateBar, "img/playable/ult" + std::to_string(spriteNumber) + ".png");
    ultimateBar->AddComponent(newUltimateSprite);
    ultimateBar->RemoveComponent(ultimateBarSprite);
    ultimateBarSprite = newUltimateSprite;
    this->ultimateBarSpriteNumber = spriteNumber;
  }
}

void Playable::ManageInput(float dt) {
  int currentUltimateSpriteNumber = points/(POINTS_TO_ULTIMATE/6.0);

  if (currentUltimateSpriteNumber != this->ultimateBarSpriteNumber) {
    this->UpdateUltimateBarSprite(currentUltimateSpriteNumber);
  }
  
  if (this->IsDead()) {
    this->currentState = DYING;
  } else {
    if((InputManager::GetInstance().GetLastsPressKeys() == "FG") && (not this->IsAttacking())) {
      this->currentState = COMBO;

      InputManager::GetInstance().SetLastsPressKeys("");
    }
    else if(InputManager::GetInstance().KeyPress(A_KEY) && (not this->IsAttacking())) {
      this->currentState = BASIC_ATTACK_ONE;
    }
    else if(InputManager::GetInstance().KeyPress(S_KEY) && (not this->IsAttacking())) {
      this->currentState = BASIC_ATTACK_TWO;
    }
    else if(InputManager::GetInstance().KeyPress(D_KEY) && (not this->IsAttacking()) && this->UltimateReady()) {
      this->currentState = ULTIMATE_BEGIN;
      this->points = 0;
    }
    else if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(0); // FIXME: This shouldn't be here. Move to Update
      this->associated.box.UpdatePos((direction * this->speed) * dt);
      this->orientation = RIGHT;
    }
    else if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(0);
      this->associated.box.UpdatePos((direction * -this->speed) * dt);
      this->orientation = LEFT;
    }
    if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
      this->currentState = MOVING;
      Vec2 direction = Vec2::GetSpeed(90);
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }
    if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
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

bool Playable::UltimateReady() {
  return points >= POINTS_TO_ULTIMATE;
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