#include "Enemy.h"
#include "Collider.h"
#include "Veteran.h"

#include <iostream> 

Enemy::Enemy(GameObject &associated) : Fighter(associated) {
  this->hp = ENEMY_HP;
  this->speed = ENEMY_SPEED;
  this->attackCooldown = Timer();
  this->attackCooldown.Set(ATTACK_COOLDOWN);
}

Enemy::~Enemy() {}
void Enemy::Start() {}

bool Enemy::TargetIsInRange() {
  float enemyAttackX = this->GetColliderBox().GetCenter().x;
  float enemyAttackY = (this->GetColliderBox().y + this->GetColliderBox().h);
  float enemyAttackWidth = this->GetColliderBox().w;
  float enemyXRange = (enemyAttackWidth/2.0) + (this->target.w/2.0);

  float targetDistanceX = abs(target.GetCenter().x - enemyAttackX);
  float targetDistanceY = abs((target.y + target.h) - enemyAttackY);

  return((enemyXRange > targetDistanceX) && (ATTACK_Y_RANGE > targetDistanceY));
}

void Enemy::ManageInput(float dt) {
  if(Veteran::player != nullptr) {
    this->target = Veteran::player->GetColliderBox();
    
    if(this->IsDead()){
      this->currentState = DYING;
    }
    else if(this->attackCooldown.Get() < ATTACK_COOLDOWN && not this->IsAttacking()) {
      if(sprite[currentState]->IsFinished())
        this->currentState = IDLE;
    }
    else if (TargetIsInRange()) {
      this->currentState = BASIC_ATTACK_ONE;
      this->attackCooldown.Restart();
    }
    // else if(this->sprite[MOVING]->IsActive()) { // FIXME: Why?
    //   if(this->sprite[MOVING]->IsFinished())
    // }
    else {
      this->currentState = MOVING;
    }

    if (this->currentState != DYING) {
      if (this->target.GetCenter().x + 10 < this->GetBox().GetCenter().x)
        this->orientation = LEFT;
      else
        this->orientation = RIGHT;

      if (this->orientation == LEFT)
        this->associated.flip = SDL_FLIP_HORIZONTAL;
      else
        this->associated.flip = SDL_FLIP_NONE;
    }
  }
  else {
    this->currentState = IDLE;
  }
}

void Enemy::Update(float dt) {
  Fighter::Update(dt);
  this->attackCooldown.Update(dt);
}

void Enemy::HandleMovement(float dt) {
  if(not this->sprite[MOVING]->IsActive()) {
    this->ActivateSprite(MOVING);
    // this->sound[MOVING]->Play(-1);
  }

  Vec2 direction = this->associated.box.GetCenter().GetSpeed(this->target.GetCenter());
  this->associated.box.UpdatePos((direction * this->speed) * dt);
}

void Enemy::HandleDying(float) {
  if(not this->sprite[DYING]->IsActive()) {
    this->associated.GetComponent("Collider")->Desactivate();
    this->ActivateSprite(DYING);
    this->associated.box.x += (this->orientation == RIGHT ? -1 : 0) * this->sprite[MOVING]->GetWidth();
    // this->sound[DYING]->Play(1);
  }
  if(this->sprite[DYING]->IsFinished()){
    this->associated.RequestDelete();
  }
}

bool Enemy::Is(std::string type) {
  return (type == "Enemy" || Fighter::Is(type));
}

void Enemy::NotifyCollision(GameObject &other) {
  Fighter::NotifyCollision(other);
}

bool Enemy::IsOpponent(GameObject &other) {
  return (not other.Has("Enemy"));
}