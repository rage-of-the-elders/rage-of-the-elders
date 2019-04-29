#include "Minion.h"
#include "Sprite.h"
#include "Game.h"
#include "Bullet.h"
#include <iostream>

#define CONST 45

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg) : Component(associated) {

  this->alienCenter = (alienCenter.lock());
  this->associated.AddComponent(new Sprite(associated, "img/minion.png"));
  this->arc = arcOffsetDeg;
}

void Minion::Shoot(Vec2 target) {
  float angle = this->associated.box.GetCenter().GetAngle(target);
  float speed = 500;
  float damage = 10;
  float maxDistance = this->associated.box.GetCenter().GetDistance(target);
  GameObject *bullet = new GameObject();
  bullet->AddComponent(new Bullet(associated, angle, speed, damage, maxDistance, "img/minionbullet1.png"));

  bullet->box.SetPos(associated.box.GetCenter() - Vec2(bullet->box.w / 2, bullet->box.h / 2));
  Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::Update(float dt) {
  // this->arc += CONST*dt;
  // Vec2 a = Vec2(200, 0);
  // a = a.Rotate(0, arc);
  // this->alienCenter.box.GetCenter() += a

  // ?????????????????????????????????????????????????????????????/
  arc += 60;
  std::cout << ((alienCenter.lock().get()) == nullptr);
  // associated.rotation = arc - 90;

  // associated.box.x = alienCenter.lock()->box.x;
  // associated.box.y = alienCenter.lock()->box.y;
  // printf("%f %f\n", alienCenter.lock()->box.x, alienCenter.lock()->box.y);
  // printf("%f %f\n", alienCenter.lock()->box.x, alienCenter.lock()->box.y);
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
  return type == "Minion";
}
