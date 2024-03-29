#include "Boss.h"
#include "Collider.h"
#include "Playable.h"
#include "Camera.h"
#include "GameData.h"

#include <iostream>

Boss::Boss(GameObject &associated) : Enemy(associated) {
  this->hp = BOSS_HP;
  this->speed = BOSS_SPEED;
  this->enemyAttackCooldown = 10;
  this->damage[BASIC_ATTACK_ONE] = 1;
  this->bossIsOnLeft = true;
  this->bossAlredyMove = true;
  this->timesThatTheBossTurnArround = 0;
  this->frozenTime = Timer();
  this->turnArroundTimes = 5;
  this->shadow->SetShadowScale({3.5, 1});

  std::string character = "boss";
  this->sprite[MOVING] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[BASIC_ATTACK_ONE] = new Sprite(this->associated, "img/" + character + "/moving.png", 25, 0.04, 0, true);
  this->sprite[IDLE] = new Sprite(this->associated, "img/" + character + "/idle.png", 25, 0.04, 0, true);
  this->sprite[FROZEN] = new Sprite(this->associated, "img/" + character + "/frozen.png", 25, 0.04, 0, true);
  this->sprite[HURTING] = new Sprite(this->associated, "img/" + character + "/hurting.png", 25, 0.04, 0, false);
  this->sprite[DYING] = new Sprite(this->associated, "img/" + character + "/dying.png", 25, 0.08, 0, false);

  this->associated.AddComponent(this->sprite[IDLE]);
  this->associated.AddComponent(this->sprite[MOVING]);
  this->associated.AddComponent(this->sprite[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sprite[HURTING]);
  this->associated.AddComponent(this->sprite[DYING]);
  this->associated.AddComponent(this->sprite[FROZEN]);


  this->ActivateSprite(MOVING);

  this->bodyColliderBox = new Collider(this->associated, {0.8,1});
  this->attackColliderBox = new Collider(this->associated, {0.8,1});
  this->associated.AddComponent(this->bodyColliderBox);
  this->associated.AddComponent(this->attackColliderBox);

  this->sound[HURTING] = new Sound(this->associated, "audio/boss/hurting.ogg");
  // this->associated.AddComponent(new Collider(this->associated, {0.4,0.9}));
}

Boss::~Boss() {}

void Boss::ResetSpeed() {
  this->speed = 600;
}

bool Boss::Is(std::string type) {
  return (type == "Boss" || Enemy::Is(type));
}

void Boss::Update(float dt) {
  Enemy::Update(dt);
  this->frozenTime.Update(dt);

}

void Boss::ManageInput(float dt) {
  this->attackCooldown.Update(dt);
  if(Playable::player != nullptr) {
    this->target = Playable::player->GetColliderBox();
    this->tagetPlayer = Playable::player->GetFoot();

    if(this->IsDead()){
      this->currentState = DYING;
    }
    else if (TargetIsInRange() && this->currentState != FROZEN) {
      Playable::player->ApplyDamage(1);
      Playable::player->SetState(HURTING);
    }
    else if(this->currentState != IDLE && this->currentState != FROZEN) {
      this->currentState = MOVING;
    }

    else if(this->attackCooldown.Get() > 0.1 && this->currentState == IDLE && this->currentState != FROZEN){
      this->currentState = MOVING;
    }

    else if(this->timesThatTheBossTurnArround >= this->turnArroundTimes && this->currentState != FROZEN && this->currentState != HURTING) {
      this->currentState = FROZEN;
      this->frozenTime.Restart();
    }

    else if(this->timesThatTheBossTurnArround >= this->turnArroundTimes && this->frozenTime.Get() > 6) {
      this->timesThatTheBossTurnArround = 0;
      this->currentState = MOVING;
    }

    else if(this->currentState == FROZEN && this->frozenTime.Get() > 6){
      this->currentState = MOVING;
    }
    if (this->currentState != DYING) {
      if (this->target->GetCenter().x + 10 < this->GetBox().GetCenter().x)
        this->orientation = LEFT;
      else
        this->orientation = RIGHT;
      if (this->orientation == LEFT)
        this->associated.flip = SDL_FLIP_HORIZONTAL;
      else
        this->associated.flip = SDL_FLIP_NONE;
    }

    if(this->hp <= 400) {
      this->turnArroundTimes = 6;
    }
    if(this->hp <= 300) {
      this->turnArroundTimes = 8;
    }
    if(this->hp <= 200) {
      this->turnArroundTimes = 10;
    }
    if(this->hp <= 100) {
      this->turnArroundTimes = 12;
      this->speed = 800;
    }
  }
}

void Boss::HandleMovement(float dt) {
    if(not this->sprite[MOVING]->IsActive()) {
      this->ActivateSprite(MOVING);
    }
    Vec2 targetDirection = Vec2(Camera::position.x, this->tagetPlayer.y);//, Camera::position.y + (Camera::position.y - this->tagetPlayer.y));
    if(this->bossIsOnLeft) {
      Vec2 direction = this->GetFoot().GetCenter().GetSpeed(Vec2(targetDirection.x, targetDirection.y));
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }
    else {
      Vec2 direction = this->GetFoot().GetCenter().GetSpeed(Vec2(targetDirection.x + 1280, targetDirection.y));
      this->associated.box.UpdatePos((direction * this->speed) * dt);
    }
    if(this->associated.box.x < (targetDirection.x + HALF_OF_THE_SCREEN)) {
      if((this->associated.box.GetPos().x - targetDirection.x) < LEFT_GAP_TO_KEEP_BOSS_ON_THE_SCREEN) {
        this->currentState = IDLE;
        this->attackCooldown.Restart();
        this->bossIsOnLeft = (not this->bossIsOnLeft);
        this->bossAlredyMove = false;
        this->timesThatTheBossTurnArround++;
      }
    }
    else if (this->associated.box.x > (targetDirection.x + HALF_OF_THE_SCREEN)) {
      if(not this->bossAlredyMove) {
        if(((targetDirection.x + WIDTH_OF_THE_SCREEN) - this->associated.box.GetPos().x) < RIGHT_GAP_TO_KEEP_BOSS_ON_THE_SCREEN) {
          this->currentState = IDLE;
          this->attackCooldown.Restart();
          this->bossIsOnLeft = (not this->bossIsOnLeft);
          this->timesThatTheBossTurnArround++;
        }
      }
    }
}

void Boss::HandleDying(float) {
  if(not this->sprite[DYING]->IsActive()) {
    this->associated.GetComponent("Collider")->Desactivate();
    this->ActivateSprite(DYING);
    this->associated.box.x += (this->orientation == RIGHT ? -100 : 0);
    
    GameObject *explosion1GO = new GameObject(this->associated);
    Sprite *explosion1 = new Sprite(*explosion1GO, "img/explosion.png", 7, 0.07, (7 * 0.07), false);
    explosion1GO->box.SetPos(this->associated.box.GetCenter().x + 50, this->associated.box.GetCenter().y);

    GameObject *explosion2GO = new GameObject(this->associated);
    Sprite *explosion2 = new Sprite(*explosion2GO, "img/explosion.png", 7, 0.07, (7 * 0.07), false);
    explosion2GO->box.SetPos(this->associated.box.GetCenter().x - 50, this->associated.box.GetCenter().y);

    GameObject *explosion3GO = new GameObject(this->associated);
    Sprite *explosion3 = new Sprite(*explosion3GO, "img/explosion.png", 7, 0.07, (7 * 0.07), false);
    explosion3GO->box.SetPos(this->associated.box.GetCenter().x, this->associated.box.GetCenter().y + 50);

    GameObject *explosion4GO = new GameObject(this->associated);
    Sprite *explosion4 = new Sprite(*explosion4GO, "img/explosion.png", 7, 0.07, (7 * 0.07), false);
    explosion4GO->box.SetPos(this->associated.box.x, this->associated.box.y - 50);

    
    this->associated.AddComponent(explosion1);
    this->associated.AddComponent(explosion2);
    this->associated.AddComponent(explosion3);
    this->associated.AddComponent(explosion4);
  }
  if (this->sprite[DYING]->IsFinished())
  {
    shadow->RequestDelete();
    StageState::DecreaseEnemiesCount();
    GameData::playerVictory = true;
    this->associated.RequestDelete();
  }
}
