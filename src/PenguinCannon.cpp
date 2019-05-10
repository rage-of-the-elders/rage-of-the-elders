#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon(GameObject &associated, GameObject& penguinBody) : Component(associated) {
  this->pbody = Game::GetInstance().GetState().GetObjectPtr(&penguinBody);
  this->angle = 0;
  this->associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
}

void PenguinCannon::Update(float dt) {
  if(not this->pbody.expired()) { // TODO: Move to method
    this->associated.box.SetCenterPos(this->pbody.lock()->box.GetCenter());
    this->angle = this->associated.box.GetCenter().GetAngle(InputManager::GetInstance().GetMousePos());
    this->associated.angleDeg = angle;

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
      this->Shoot();
    }
  } else {
    this->associated.RequestDelete();
  }
}

void PenguinCannon::Shoot() {
  float bulletSpeed = 150;
  float damage = 10;
  Vec2 mousePos = InputManager::GetInstance().GetMousePos();
  float maxDistance = this->associated.box.GetCenter().GetDistance(mousePos);
  int frameCount = 4;
  float frameTime = 0.5;

  GameObject *bullet = new GameObject();
  Vec2 cannonCenter = this->associated.box.GetCenter();
  bullet->box.SetCenterPos(cannonCenter);
  bullet->AddComponent(new Bullet(*bullet, this->angle, bulletSpeed, damage,
                                  maxDistance, "img/penguinbullet.png",
                                  frameCount, frameTime));
  Game::GetInstance().GetState().AddObject(bullet);
}

void PenguinCannon::Render() {
  
}

bool PenguinCannon::Is(std::string type) {
  return type == "PenguinCannon";
}
