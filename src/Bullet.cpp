#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite) : Component(associated) {
  this->associated.AddComponent(new Sprite(associated, sprite));
  this->speed = Vec2(Vec2::Cos(angle), Vec2::Sin(angle)) * speed;
  this->damage = damage;
  this->distanceLeft = maxDistance;
}

Bullet::~Bullet() {
}

void Bullet::Update(float dt) {
  if (this->distanceLeft > 0) {
    this->associated.box.x += this->speed.x;  
    this->associated.box.y += this->speed.y;
    this->distanceLeft -= Vec2().GetDistance(Vec2(this->speed.x*dt, this->speed.y*dt));
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
