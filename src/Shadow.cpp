#include "Shadow.h"
#include "Sprite.h"
#include "Game.h"

Shadow::Shadow(GameObject &associated, Vec2 offset) : Component(associated) {
  this->offset = offset;
  this->associated.AddComponent(new Sprite(this->associated, "img/fighter/shadow.png"));
}

Shadow::~Shadow() {}

void Shadow::Update(float) {}

void Shadow::RequestDelete() {
  this->associated.RequestDelete();
}

void Shadow::UpdatePos(Vec2 footPosition) {
    // puts("upd");
  if (not this->associated.IsDead()) {
    // puts("vou atuali");
    float xCenterPos = footPosition.x + this->offset.x;
    float yCenterPos = footPosition.y + this->offset.y + 7;
    this->associated.box.SetCenterPos(xCenterPos, yCenterPos);
  } else {
    // puts("morreu mlk");
  }
  // puts("after");
}

void Shadow::Render() {

}

bool Shadow::Is(std::string type) {
  return(type == "Shadow");
}
