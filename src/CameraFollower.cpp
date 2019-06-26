#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &associated, Vec2 offset) : Component(associated) {
  this->offset = offset;
}

void CameraFollower::Update(float) {
  this->associated.box.x = Camera::position.x + CameraFollower::offset.x;
  this->associated.box.y = Camera::position.y + CameraFollower::offset.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
  return type == "CameraFollower";
}
