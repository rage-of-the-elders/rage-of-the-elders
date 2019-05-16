#include "Alien.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "MathHelper.h"
#include "Collider.h"
#include "Bullet.h"
#include "PenguinBody.h"

#include <map>

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
  this->hp = 100;
  this->speed = Vec2();
  this->minionArray = std::vector<std::weak_ptr<GameObject>>();
  this->nMinions = nMinions;
  this->state = AlienState::RESTING;
  this->destination= Vec2();
  this->restTimer = Timer();

  this->associated.AddComponent(new Sprite(associated, "img/alien.png"));
  this->associated.AddComponent(new Collider(associated, 0.5));
  Alien::alienCount++;
}

Alien::~Alien() {
  this->minionArray.clear();
  Alien::alienCount--;
}

void Alien::Start() {
  for (int i = 0; i < this->nMinions; i++) {
    GameObject *go = new GameObject();
    go->AddComponent(new Minion(*go, this->associated, i * (360.0 / this->nMinions)));
    minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(go));
  }
}

void Alien::Update(float dt) {
  this->associated.angleDeg -= ALIEN_ROTATION*dt;

  if(PenguinBody::player) {
    switch (this->state) {
    case AlienState::RESTING: {
      this->restTimer.Update(dt);

      if (this->restTimer.Get() > ALIEN_COOLDOWN) {
        this->destination = PenguinBody::player->GetPenguinCenter();
        this->state = AlienState::MOVING;
        // this->restTimer.Restart();
      }
    } break;

    case AlienState::MOVING: {
      Vec2 pos = this->associated.box.GetCenter();
      Vec2 speed = pos.GetSpeed(this->destination) * ALIEN_BASE_SPEED;

      if ((pos.x + speed.x * dt > this->destination.x && this->destination.x > pos.x)
          || (pos.x + speed.x * dt < this->destination.x && this->destination.x < pos.x)) {
        pos.x = this->destination.x;
      } else {
        pos.x += speed.x * dt;
      }
      if ((pos.y + speed.y * dt > this->destination.y && this->destination.y > pos.y)
          || (pos.y + speed.y * dt < this->destination.y && this->destination.y < pos.y)) {
        pos.y = this->destination.y;
      } else {
        pos.y += speed.y * dt;
      }
      this->associated.box.SetCenterPos(pos);

      if (Math::Equals(pos.x, this->destination.x) && Math::Equals(pos.y, this->destination.y)) {
        this->state = AlienState::RESTING;
        this->restTimer.Restart();
        this->destination = PenguinBody::player->GetPenguinCenter();

        if (this->minionArray.size() > 0) {
          Minion *minion = (Minion *) minionArray[GetNearestMinion(this->destination)].lock()->GetComponent("Minion");
          minion->Shoot(this->destination);
        }
      }
    } break;

    default:
      break;
    }

  }

  if(this->IsDead())
    this->associated.RequestDelete();
}


void Alien::Render() {
  
}

bool Alien::Is(std::string type) {
  return type == "Alien";
}

bool Alien::IsDead() {
  return this->hp <= 0;
}

int Alien::GetNearestMinion(Vec2 target) {
  std::map<float, int> distances;
  int idx = 0;
  for(auto &i : this->minionArray) {
    distances[(i.lock()->box.GetCenter().GetDistance(target))] = idx++;
  }

  return distances.begin()->second;
}

void Alien::ApplyDamage(int damage) {
  this->hp -= damage;

  if (this->IsDead()) {
    GameObject *go = new GameObject();
    go->box = this->associated.box;

    int frameCount = 4;
    float frameTime = 0.5;
    go->AddComponent(new Sprite(*go, "img/aliendeath.png", frameCount, frameTime, frameCount * frameTime));

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    Game::GetInstance().GetCurrentState().AddObject(go);
    Sound *sound = (Sound *) go->GetComponent("Sound");
    sound->Play(1);
  }
}

void Alien::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet")) {
    Bullet *bullet = (Bullet *) other.GetComponent("Bullet");
    if (not bullet->TargetsPlayer())
      this->ApplyDamage(bullet->GetDamage());
  }
}
