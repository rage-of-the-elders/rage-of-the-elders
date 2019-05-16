#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include "MathHelper.h"
#include "Collider.h"
#include <iostream>

#define MINION_ROTATION 10

Minion::Minion(GameObject &associated, GameObject &alienCenter,
               float arcOffsetDeg) : Component(associated) {
  this->alienCenter = Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter);

  Sprite *minionSprite = new Sprite(associated, "img/minion.png");
  minionSprite->SetScaleX(Math::GetRand(1.0, 1.5));
  this->associated.AddComponent(minionSprite);
  this->associated.AddComponent(new Collider(associated));

  this->arc = arcOffsetDeg;
}

void Minion::Shoot(Vec2 target) {
  float angle = this->associated.box.GetCenter().GetAngle(target);
  float speed = 80;
  float damage = 10;
  float maxDistance = this->associated.box.GetCenter().GetDistance(target);
  int frameCount = 3;
  float frameTime = 0.85;

  GameObject *bullet = new GameObject();
  bullet->AddComponent(new Bullet(*bullet, angle, speed, damage, maxDistance, "img/minionbullet2.png",
                                   frameCount, frameTime, true));
  bullet->box.SetPos(this->associated.box.GetCenter());
  Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void Minion::Update(float dt) {
  if(not alienCenter.expired()) {
    this->arc += MINION_ROTATION*dt;
    associated.angleDeg = arc - 90;

    Vec2 newPos = Vec2().Rotate(250, arc) + this->alienCenter.lock()->box.GetCenter();
    associated.box.SetCenterPos(newPos);
  } else {
    this->associated.RequestDelete();
  }
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
  return type == "Minion";
}
