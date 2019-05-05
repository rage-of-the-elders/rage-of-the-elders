#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include <iostream>

#define ROTATION 10

Minion::Minion(GameObject &associated, GameObject &alienCenter,
               float arcOffsetDeg) : Component(associated) {

  this->alienCenter = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);
  this->associated.AddComponent(new Sprite(associated, "img/minion.png"));
  this->arc = arcOffsetDeg;
}

void Minion::Shoot(Vec2 target) {
  puts("shoot");
  // float angle = this->associated.box.GetCenter().GetAngle(target);
  // float speed = 500;
  // float damage = 10;
  // float maxDistance = this->associated.box.GetCenter().GetDistance(target);
  // GameObject *bullet = new GameObject();
  // bullet->AddComponent(new Bullet(associated, angle, speed, damage, maxDistance, "img/minionbullet1.png"));

  // bullet->box.SetPos(associated.box.GetCenter() - Vec2(bullet->box.w / 2, bullet->box.h / 2));
  // Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::Update(float dt) {
  if(not alienCenter.expired()) {
    this->arc += ROTATION*dt;

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