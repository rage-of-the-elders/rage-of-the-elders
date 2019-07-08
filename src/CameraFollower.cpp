#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &associated, Vec2 offset, bool centered) : Component(associated) {
  this->offset = offset;
  this->centered = centered;
}

void CameraFollower::Update(float) {
  this->associated.box.x = Camera::position.x + CameraFollower::offset.x;
  this->associated.box.y = Camera::position.y + CameraFollower::offset.y;

  if (this->centered){
    this->associated.box.x -= associated.box.w/2;
    this->associated.box.y -= associated.box.h/2;
  }
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
  return type == "CameraFollower";
}
