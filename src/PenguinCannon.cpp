#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Collider.h"
#include "PenguinBody.h"

PenguinCannon::PenguinCannon(GameObject &associated, GameObject& penguinBody) : Component(associated) {
  this->pbody = Game::GetInstance().GetState().GetObjectPtr(&penguinBody);
  this->angle = 0;
  this->associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
  this->associated.AddComponent(new Collider(associated));
  this->shootCooldown = Timer();
}

void PenguinCannon::Update(float dt) {
  if(not this->pbody.expired()) { // TODO: Move to method
    this->associated.box.SetCenterPos(this->pbody.lock()->box.GetCenter());
    this->angle = this->associated.box.GetCenter().GetAngle(InputManager::GetInstance().GetMousePos());
    this->associated.angleDeg = angle;
    this->shootCooldown.Update(dt);

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
      this->Shoot();
    }
  } else {
    this->associated.RequestDelete();
  }
}

void PenguinCannon::Shoot() {
  if (this->shootCooldown.Get() > SHOOT_COOLDOWN) {
    float bulletSpeed = 100;
    float damage = 10;
    Vec2 mousePos = InputManager::GetInstance().GetMousePos();
    float maxDistance = this->associated.box.GetCenter().GetDistance(mousePos);
    int frameCount = 4;
    float frameTime = 0.85;

    GameObject *bullet = new GameObject();
    Vec2 cannonCenter = this->associated.box.GetCenter();
    bullet->box.SetCenterPos(cannonCenter);
    bullet->AddComponent(new Bullet(*bullet, this->angle, bulletSpeed, damage,
                                    maxDistance, "img/penguinbullet.png",
                                    frameCount, frameTime, false));
    Game::GetInstance().GetState().AddObject(bullet);
    this->shootCooldown.Restart();
  }
}

void PenguinCannon::Render() {
  
}

bool PenguinCannon::Is(std::string type) {
  return type == "PenguinCannon";
}

void PenguinCannon::ApplyDamage(int damage) {
  if (not this->pbody.expired()) {
    PenguinBody *body = (PenguinBody *) (this->pbody.lock()->GetComponent("PenguinBody"));
    body->ApplyDamage(damage);
  }
}

void PenguinCannon::NotifyCollision(GameObject &other) {
  if(other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *) other.GetComponent("Bullet");
    if (bullet->TargetsPlayer())
      this->ApplyDamage(bullet->GetDamage());
  }
}