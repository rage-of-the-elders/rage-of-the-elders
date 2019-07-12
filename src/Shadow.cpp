#include "Shadow.h"
#include "Sprite.h"
#include "Game.h"

Shadow::Shadow(GameObject &associated, Vec2 offset) : Component(associated) {
  this->offset = offset;
  this->sprite = new Sprite(this->associated, "img/fighter/shadow.png");
  this->sprite->SetScaleX(1.5, 1);
  this->associated.AddComponent(this->sprite);
}

Shadow::~Shadow() {}

void Shadow::Update(float) {}

void Shadow::RequestDelete() {
  this->associated.RequestDelete();
}

void Shadow::UpdatePos(Vec2 footPosition) {
  if (not this->associated.IsDead()) {
    float xCenterPos = footPosition.x + this->offset.x;
    float yCenterPos = footPosition.y + this->offset.y + 7;
    this->associated.box.SetCenterPos(xCenterPos, yCenterPos);
  } else {
    // dead
  }
}

void Shadow::Render() {

}

void Shadow::SetShadowScale(Vec2 scale) {
  this->sprite->SetScaleX(scale.x, scale.y);
}

bool Shadow::Is(std::string type) {
  return(type == "Shadow");
}
