#include "Fighter.h"
#include "Camera.h"
#include "Game.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"
#include "Collision.h"
#include "Veteran.h"
#include "Bullet.h"
#include <iostream>

Fighter::Fighter(GameObject &associated) : Component(associated) {
  this->hp = FIGHTER_HP;       // Maybe we should receive this on the constructor
  this->speed = FIGHTER_SPEED; // Maybe we should receive this on the constructor
  this->currentState = IDLE;
  this->orientation = LEFT;
  this->active = true;
  this->storedState = INVALID;
  this->ultimateDuration = Timer();
  this->damage[BASIC_ATTACK_ONE] = 10;
  this->comboCount = 0;
  this->points = 0;
  this->shootCooldown = Timer();
  this->timeToDelete = Timer();

  this->sprite = std::vector<Sprite *>(LAST);
  this->sound = std::vector<Sound *>(LAST);

  this->sound[MOVING] = new Sound(this->associated, "audio/walking.ogg");
  this->sound[BASIC_ATTACK_ONE] = new Sound(this->associated, "audio/punch.ogg");
  this->sound[BASIC_ATTACK_TWO] = new Sound(this->associated, "audio/walking_stick_hit.ogg");
  this->sound[COMBO] = new Sound(this->associated, "audio/punch.ogg");
  this->sound[ULTIMATE_FINAL] = new Sound(this->associated, "audio/machine_gun.ogg");
  this->sound[ULTIMATE_MIDLE] = new Sound(this->associated, "audio/machine_gun_shot.ogg");
  this->sound[HIT] = new Sound(this->associated, "audio/hit.ogg");

  this->associated.AddComponent(this->sound[MOVING]);
  this->associated.AddComponent(this->sound[BASIC_ATTACK_ONE]);
  this->associated.AddComponent(this->sound[BASIC_ATTACK_TWO]);
  this->associated.AddComponent(this->sound[COMBO]);
  this->associated.AddComponent(this->sound[ULTIMATE_FINAL]);
  this->associated.AddComponent(this->sound[ULTIMATE_MIDLE]);
  this->associated.AddComponent(this->sound[HIT]);
}

Fighter::~Fighter() {}
void Fighter::Start() {}

void Fighter::UpdateStateMachine(float dt) {
  switch (this->currentState) {
  case MOVING: {
    HandleMovement(dt);
  } break;
  case IDLE: {
    if(not this->sprite[IDLE]->IsActive()) {
      this->ActivateSprite(IDLE);
    }
  } break;
  case BASIC_ATTACK_ONE: {
    HandleAttackOne(dt);
} break;
  case BASIC_ATTACK_TWO: {
    HandleAttackTwo(dt);
  } break;
  case COMBO: {
    HandleCombo(dt);
  } break;
  case ULTIMATE_BEGIN: {
    HandleUltimateBegin(dt);
  } break;
  case ULTIMATE_MIDLE: {
    HandleUltimateMidle(dt);
  } break;
  case ULTIMATE_FINAL: {
    HandleUltimateFinal(dt);
  } break;
  case HURTING: {
    HandleHurting(dt);
  } break;
  case DYING: {
    HandleDying(dt);
  } break;
  case FROZEN: {
    HandleFrozen(dt);
  } break;
  default:
    break;
  }

  if (this->currentState != ULTIMATE_MIDLE) {
    // if (this->sound[ULTIMATE_MIDLE]->IsPlaying())
      // this->sound[ULTIMATE_MIDLE]->Stop();
  }

}

void Fighter::Update(float dt) {

  if(this->IsDead() || this->storedState == INVALID) {
    ManageInput(dt);
  } else {
    this->currentState = storedState;
  }

  this->shootCooldown.Update(dt);
  UpdateStateMachine(dt);
}

void Fighter::Render() {
#ifdef DEBUG

  Vec2 center(this->associated.box.GetCenter());
  SDL_Point points[5];

  Vec2 point = (Vec2(this->GetFoot().x, this->GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x + this->GetFoot().w, this->GetFoot().y) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x + this->GetFoot().w, this->GetFoot().y + this->GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(this->GetFoot().x, this->GetFoot().y + this->GetFoot().h) - center).Rotate(associated.angleDeg) + center - Camera::position;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);

#endif
}

bool Fighter::Is(std::string type) {
  return (type == "Fighter");
}

void Fighter::NotifyCollision(GameObject &other) {
  if(other.Has("Barrier")) { // TODO: mover pra função, tá horrível
    Collider *colliderBox = (Collider *)this->associated.GetComponent("Collider");
    Rect fighterFoot = this->GetFoot();

    if (Collision::IsColliding(fighterFoot, other.box, this->associated.angleDeg, other.angleDeg)) {

      float collisionX = std::min( abs(fighterFoot.x + fighterFoot.w - other.box.x), abs(fighterFoot.x - (other.box.x + other.box.w)));
      float collisionY = std::min(abs(fighterFoot.y + fighterFoot.h - other.box.y), abs(fighterFoot.y - (other.box.y + other.box.h)));

      if (collisionX > collisionY) {
        float objY;
        float distanceToBottom = fighterFoot.y - (other.box.y + other.box.h);
        float distanceToTop = (fighterFoot.y + fighterFoot.h) - other.box.y;

        if (abs(distanceToBottom) > abs(distanceToTop)) {
          objY = other.box.y;

          if ((fighterFoot.y + fighterFoot.h) > objY) {
            this->associated.box.y = other.box.y - ((this->associated.box.h - colliderBox->GetHeigth()) / 2) -
                                     colliderBox->GetHeigth();
          }
        }
        else {
          objY = other.box.y + other.box.h;

          if (fighterFoot.y < objY) {
            this->associated.box.y = other.box.y + other.box.h -
                                     ((this->associated.box.h - colliderBox->GetHeigth()) / 2) -
                                     colliderBox->GetHeigth() + fighterFoot.h;
          }
        }
      }
      else {
        float objX;
        float distanceToRight = fighterFoot.x - (abs(other.box.x) + other.box.w);
        float distanceToLeft = (fighterFoot.x + fighterFoot.w) - abs(other.box.x);

        if (abs(distanceToRight) > abs(distanceToLeft)) {
          objX = other.box.x;

          if ((fighterFoot.x + fighterFoot.w) > objX) {
            this->associated.box.x = other.box.x - colliderBox->GetWidth() - ((this->associated.box.w - colliderBox->GetWidth()) / 2);
          }
        }
        else {
          objX = other.box.x + other.box.w;

          if (fighterFoot.x < objX) {
            this->associated.box.x = other.box.x + other.box.w - ((this->associated.box.w - colliderBox->GetWidth()) / 2);
          }
        }
      }
    }
  }
  else if (other.Has("Fighter") && this->IsOpponent(other))
  {
    if (not this->IsHurting()) {
      Fighter *opponent = (Fighter *)other.GetComponent("Fighter");
      if (this->TargetIsInYRange(opponent->GetColliderBox())) {
        if (opponent->IsAttacking() && not this->IsDead()) {
          if (this->CanAttack(opponent->GetOrientation(), opponent->GetBox())) {
            this->storedState = HURTING;
            this->ApplyDamage(opponent->GetDamage());
            this->sound[HIT]->Play(1);
            if (other.Has("Playable")) {
              this->MoveInX(FIGHTER_RECOIL * 2 * (opponent->GetOrientation() == LEFT ? -1 : 1)); // TODO: DIFFICULTY
              opponent->comboCount++;
              opponent->points++;
              puts("player bateu");
              if (opponent->comboCount > 3) {
                opponent->points += (opponent->comboCount * 0.2);
              }
            }
            else if (other.Has("Enemy")) {
              this->MoveInX(FIGHTER_RECOIL * (opponent->GetOrientation() == LEFT ? -1 : 1));
              opponent->comboCount = 0;
            }

            auto pow = new GameObject();
            int rand = (int)floor(Math::GetRand(0, 2));
            std::string file = (rand % 2 == 0 ? "img/pow.png" : "img/bam.png");
            auto sprite = new Sprite(*pow, file, 1, 0, 0.35);
            sprite->SetScaleX(0.3);
            pow->AddComponent(sprite);
            pow->box.SetCenterPos(this->GetBox().GetCenter().x, this->GetBox().y - 20);
            Game::GetInstance().GetCurrentState().AddObject(pow);
          }
        }
      }
    }
  }
  else if (other.Has("Bullet")) {
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if(this->IsAttacking() && Math::Equals(bullet->GetAngleDeg(), (this->orientation == RIGHT ? 180.0 : 0.0))) {
      bullet->SetDirection(-1, (this->orientation == RIGHT ? 0.0 : 180.0));
    }
    else if(not this->IsAttacking()){
      this->ApplyDamage(bullet->GetDamage());
      GameObject *explosionGo = new GameObject();
      explosionGo->box = bullet->GetBox();
      explosionGo->AddComponent(new Sprite(*explosionGo, "img/explosion.png", 7, 0.07, (7 * 0.07), false));
      Game::GetInstance().GetCurrentState().AddObject(explosionGo);
      Sound *explosionSound = new Sound(*explosionGo, "audio/boom.wav");
      explosionSound->Play(1);
      this->storedState = HURTING;
      if (Veteran::player != nullptr) {
        this->MoveInX(FIGHTER_RECOIL * 2 * (Veteran::player->GetOrientation() == LEFT ? -1 : 1)); // TODO: Difficulty
      }
      bullet->RemoveBullet();
    }
  }
}

bool Fighter::TargetIsInYRange(Rect targetBox) {
  float fighterAttackY = (this->GetColliderBox().y + this->GetColliderBox().h);

  float targetDistanceY = abs((targetBox.y + targetBox.h) - fighterAttackY);

  return ((ATTACK_Y_RANGE > targetDistanceY));
}

void Fighter::ActivateSprite(FighterState state)
{
  for (int enumState = FIRST; enumState < this->LAST; enumState++) {
    FighterState currentEnumState = static_cast<FighterState>(enumState);
    if (currentEnumState == state) {
      this->currentState = state;
      sprite[state]->Activate();
    }
    else if (sprite[enumState]) {
      sprite[currentEnumState]->Desactivate();
    }
  } 
}

int Fighter::GetDamage() {
  return this->damage[this->currentState];
}

Rect Fighter::GetFoot() {
  Collider *colliderBox = (Collider *)this->associated.GetComponent("Collider");
  return Rect(colliderBox->GetX(), ((colliderBox->GetY() + colliderBox->GetHeigth()) - 10), colliderBox->GetWidth(), 10);
}

bool Fighter::IsAttacking() {
  return (Math::InRange(currentState, BASIC_ATTACK_ONE, COMBO));
}

void Fighter::ApplyDamage(int damage) {
  this->hp -= damage;
}

bool Fighter::IsHurting() {
  return (currentState == HURTING);
}

bool Fighter::IsDead() {
  return (this->hp <= 0);
}

bool Fighter::CanAttack(enum Orientation targetOrientation, Rect targetRect) {
  if ((targetOrientation == Fighter::LEFT && (this->associated.box.x < targetRect.x)) ||
      (targetOrientation == Fighter::RIGHT && (this->associated.box.x > targetRect.x)))
    return true;

  return false;
}

enum Fighter::Orientation Fighter::GetOrientation() {
  return this->orientation;
}

void Fighter::HandleMovement(float) {}

void Fighter::HandleAttackOne(float) {
  if (not this->sound[BASIC_ATTACK_ONE]->IsPlaying()) {
    this->sound[BASIC_ATTACK_ONE]->Play(1);
  }
  if (not this->sprite[BASIC_ATTACK_ONE]->IsActive()) {
    this->ActivateSprite(BASIC_ATTACK_ONE);
  }
  if (this->sprite[BASIC_ATTACK_ONE]->IsFinished()) {
    this->currentState = IDLE;
    this->sprite[BASIC_ATTACK_ONE]->SetFrame(0);
    this->sprite[BASIC_ATTACK_ONE]->SetFinished(false);
  }
}

void Fighter::HandleAttackTwo(float) {
  if(not this->sprite[BASIC_ATTACK_TWO]->IsActive()) {
    this->ActivateSprite(BASIC_ATTACK_TWO);
    this->sound[BASIC_ATTACK_TWO]->Play(1);
  }
  if(this->sprite[BASIC_ATTACK_TWO]->IsFinished()) {
    this->currentState = IDLE;
    this->sprite[BASIC_ATTACK_TWO]->SetFrame(0);
    this->sprite[BASIC_ATTACK_TWO]->SetFinished(false);
  }
}

void Fighter::HandleCombo(float) {
  if(not this->sprite[COMBO]->IsActive()) {
    this->ActivateSprite(COMBO);
    this->sound[COMBO]->Play(1);
  }
  if(this->sprite[COMBO]->IsFinished()) {
    this->currentState = IDLE;
    this->sprite[COMBO]->SetFrame(0);
    this->sprite[COMBO]->SetFinished(false);
  }
}

void Fighter::HandleUltimateBegin(float) {
  if(not this->sprite[ULTIMATE_BEGIN]->IsActive()) {
    this->ActivateSprite(ULTIMATE_BEGIN);
    // this->sound[ULTIMATE_BEGIN]->Play(1);
    this->ultimateDuration.Restart();
  }
  if(this->sprite[ULTIMATE_BEGIN]->IsFinished()) {
    this->currentState = ULTIMATE_MIDLE;
    this->sprite[ULTIMATE_BEGIN]->SetFrame(0);
    this->sprite[ULTIMATE_BEGIN]->SetFinished(false);
  }
}

void Fighter::HandleUltimateMidle(float dt) {
  // this->sound[ULTIMATE_BEGIN]->Stop();

  if(not this->sound[ULTIMATE_MIDLE]->IsPlaying())
    this->sound[ULTIMATE_MIDLE]->Play(1);

  if(not this->sprite[ULTIMATE_MIDLE]->IsActive()) {
    this->ActivateSprite(ULTIMATE_MIDLE);
  }

  this->Shoot("img/veteran/shoot.png", 6);
  this->ultimateDuration.Update(dt);
  // if(this->sprite[ULTIMATE_MIDLE]->IsFinished()) {
  //   this->currentState = ULTIMATE_FINAL;
  //   this->sprite[ULTIMATE_MIDLE]->SetFrame(0);
  //   this->sprite[ULTIMATE_MIDLE]->SetFinished(false);
  // }
  if(this->ultimateDuration.Get() > 4) {
    this->currentState = ULTIMATE_FINAL;
    this->ultimateDuration.Restart();
  }
}

void Fighter::HandleUltimateFinal(float) {
  if (not this->sound[ULTIMATE_MIDLE]->IsPlaying())
    this->sound[ULTIMATE_FINAL]->Play(1);

  if(not this->sprite[ULTIMATE_FINAL]->IsActive()) {
    this->ActivateSprite(ULTIMATE_FINAL);
    // this->sound[ULTIMATE_MIDLE]->Stop();
  }
  if(this->sprite[ULTIMATE_FINAL]->IsFinished()) {
    this->currentState = IDLE;
    this->sprite[ULTIMATE_FINAL]->SetFrame(0);
    this->sprite[ULTIMATE_FINAL]->SetFinished(false);
  }
}

void Fighter::HandleHurting(float) {
  if(not this->sprite[HURTING]->IsActive()) {
    this->ActivateSprite(HURTING);
    //Som
  }
  if(this->sprite[HURTING]->IsFinished()) {
    this->sprite[HURTING]->SetFrame(0);
    this->sprite[HURTING]->SetFinished(false);
    if(this->associated.Has("Boss"))
      this->currentState = FROZEN;
    else
      this->currentState = MOVING;
    this->storedState = INVALID;
  }
}


void Fighter::HandleDying(float dt) {
  if (not this->sprite[DYING]->IsActive()) {
    this->associated.GetComponent("Collider")->Desactivate();
    this->ActivateSprite(DYING);
    // this->associated.box.x += (this->orientation == RIGHT ? -1 : 0) * 270;
    // this->sound[DYING]->Play(1);
  }
  if (this->sprite[DYING]->IsFinished()) {
    timeToDelete.Update(dt);
    if (timeToDelete.Get() > TIME_TO_DELETE) {
      this->associated.RequestDelete();
    }
    Veteran::player = nullptr;
  }
}

void Fighter::HandleFrozen(float) {
  if(not this->sprite[FROZEN]->IsActive()) {
    this->ActivateSprite(FROZEN);
  }
}

Rect Fighter::GetColliderBox() {
  Collider *fighterColliderBox = (Collider *)this->associated.GetComponent("Collider");
  return Rect(fighterColliderBox->GetX(),
              fighterColliderBox->GetY(),
              fighterColliderBox->GetWidth(),
              fighterColliderBox->GetHeigth());
}

void Fighter::Shoot(std::string file, int frameCount) {
  if (this->shootCooldown.Get() > SHOOT_COOLDOWN) {
    float bulletSpeed = 400;
    float damage = 10;
    float maxDistance = this->associated.box.GetCenter().GetDistance(this->associated.box.GetCenter() + 600);
    float frameTime = 0.09;

    GameObject *bullet = new GameObject();
    Vec2 gunShootPosition = Vec2((this->associated.box.GetCenter().x + ((this->orientation == RIGHT ? 130 : -260))),
                                 (this->associated.box.GetCenter().y - 60));
    bullet->box.SetCenterPos(gunShootPosition);
    bullet->AddComponent(new Bullet(*bullet, this->orientation == RIGHT ? 0 : 180, ((this->orientation == RIGHT ? 1 : -1) * bulletSpeed),
                                    damage,
                                    maxDistance, file,
                                    frameCount, frameTime, true));
    Game::GetInstance().GetCurrentState().AddObject(bullet);
    this->shootCooldown.Restart();
  }
}

void Fighter::SetState(FighterState state) {
  this->currentState = state;
}
void Fighter::MoveInX(float distance) {
  this->associated.box.x += distance;
}