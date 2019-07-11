#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance,
               std::string sprite, int frameCount, float frameTime, bool targetsPlayer,
               float shooterY, std::string shooterType) : Component(associated) {
  this->associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
  this->associated.AddComponent(new Collider(associated));
  this->associated.angleDeg = angle;
  this->speed = Vec2(speed);
  this->damage = damage;
  this->distanceLeft = maxDistance;
  this->targetsPlayer = targetsPlayer;
  this->shooterY = shooterY;
  this->shooterType = shooterType;
}

void Bullet::Update(float dt) {
  if (this->distanceLeft > 0) {
    Vec2 direction = Vec2::GetSpeed(associated.angleDeg);
    this->associated.box.UpdatePos((direction.Multiply(speed)) * dt);
    this->distanceLeft -= Vec2().GetDistance(this->speed * dt);
  } else {
    this->associated.RequestDelete();
  }

  
}

void Bullet::Render() {

}

void Bullet::RemoveBullet() {
  this->associated.RequestDelete();
}

void Bullet::SetDirection(float direction) {
  this->associated.angleDeg = direction;
}

float Bullet::GetAngleDeg() {
  return this->associated.angleDeg;
}

bool Bullet::Is(std::string type) {
  return type == "Bullet";
}

int Bullet::GetDamage() {
  return this->damage;
}

void Bullet::NotifyCollision(GameObject &other) {
}

bool Bullet::TargetsPlayer() {
  return this->targetsPlayer;
}

Rect *Bullet::GetBulletBox() {
  return new Rect(this->associated.box.x, this->associated.box.y, this->associated.box.w, this->associated.box.h);
}
