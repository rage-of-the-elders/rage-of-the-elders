#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include "MathHelper.h"
#include <iostream>

#define ROTATION 13

Minion::Minion(GameObject &associated, GameObject &alienCenter,
               float arcOffsetDeg) : Component(associated) {
  this->alienCenter = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);

  Sprite *minionSprite = new Sprite(associated, "img/minion.png");
  minionSprite->SetScaleX(Math::GetRand(1.0, 1.5));
  this->associated.AddComponent(minionSprite);

  this->arc = arcOffsetDeg;
  // this->associated.angleDeg = arcOffsetDeg;
}

void Minion::Shoot(Vec2 target) {
  float angle = this->associated.box.GetCenter().GetAngle(target);
  float speed = 150;
  float damage = 10;
  float maxDistance = this->associated.box.GetCenter().GetDistance(target);
  int frameCount = 3;
  float frameTime = 0.5;

  GameObject *bullet = new GameObject();
  bullet->AddComponent(new Bullet(*bullet, angle, speed, damage, maxDistance, "img/minionbullet2.png",
                                   frameCount, frameTime));
  bullet->box.SetPos(this->associated.box.GetCenter());
  Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::Update(float dt) {
  if(not alienCenter.expired()) {
    this->arc += ROTATION*dt;
    associated.angleDeg = arc - 90;
    // this->associated.angleDeg += ROTATION*dt;

    Vec2 newPos = Vec2().Rotate(200, arc) + this->alienCenter.lock()->box.GetCenter();
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
