#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite) : Component(associated) {
  this->associated.AddComponent(new Sprite(associated, sprite));
  this->associated.angleDeg = angle;
  this->speed = Vec2::GetSpeed(angle) * speed;
  this->damage = damage;
  this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
  if (this->distanceLeft > 0) {
    this->associated.box.UpdatePos(speed * dt);
    this->distanceLeft -= Vec2().GetDistance(speed * dt);
  } else {
    this->associated.RequestDelete();
  }
}

void Bullet::Render() {
  
}

bool Bullet::Is(std::string type) {
  return type == "Bullet";
}

int Bullet::GetDamage() {
  return this->damage;
}
